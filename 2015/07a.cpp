#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>

using Value = uint16_t;
using State = std::map<std::string, Value>;

struct Node
{
	std::string out;

	explicit Node(std::string out_):
		out{ out_ }
	{}

	virtual ~Node() = default;
	virtual bool CanExecute(State const&) const =0;
	virtual void Execute(State&) =0;
};

namespace AssignLiteral
{
std::regex Regex{ "(\\d+) -> ([a-z]+)" };

struct Node: ::Node
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[2], Value(std::stoi(results[1])) };
	}

	Value value;

	Node(std::string out_, Value value_):
		::Node{ out_ },
		value(value_)
	{
		std::cout << value << " -> " << out << std::endl;
	}

	bool CanExecute(State const&) const override
	{
		return true;
	}

	void Execute(State& state) override
	{
		std::cout << out << " = " << value << std::endl;
		state[out] = value;
	}
};

}

struct UnaryNode: Node
{
	std::string in1;

	UnaryNode(std::string out_, std::string in_):
		Node{ out_ },
		in1{ in_ }
	{}

	bool CanExecute(State const& state) const override
	{
		return state.find(in1) != state.end();
	}
};

namespace Assign
{
std::regex Regex{ "([a-z]+) -> ([a-z]+)" };

struct Node: ::UnaryNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[2], results[1] };
	}

	Value value;

	Node(std::string out_, std::string const& in_):
		::UnaryNode{ out_, in_ }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << in1 << std::endl;
		state[out] = state.find(in1)->second;
	}
};
};

namespace Not
{
std::regex Regex{ "NOT ([a-z]+) -> ([a-z]+)" };

struct Node: ::UnaryNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[2], results[1] };
	}

	Node(std::string out_, std::string in_):
		::UnaryNode{ out_, in_ }
	{
		std::cout << "NOT " << in1 << " -> " << out << std::endl;
	}

	void Execute(State& state) override
	{
		std::cout << out << " = ~" << in1 << std::endl;
		state[out] = ~state.find(in1)->second;
	}
};

}

struct ShiftNode: ::UnaryNode
{
	Value amount;

	ShiftNode(std::string out_, std::string in_, Value shiftAmount):
		::UnaryNode{ out_, in_ },
		amount{ shiftAmount }
	{}
};

namespace LeftShift
{
std::regex Regex{ "([a-z]+) LSHIFT (\\d+) -> ([a-z]+)" };

struct Node: ::ShiftNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[3], results[1], Value(std::stoi(results[2])) };
	}

	Node(std::string out_, std::string in_, Value shiftAmount):
		::ShiftNode{ out_, in_, shiftAmount }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << in1 << " << " << amount << std::endl;
		state[out] = state.find(in1)->second << amount;
	}
};

}

namespace RightShift
{
std::regex Regex{ "([a-z]+) RSHIFT (\\d+) -> ([a-z]+)" };

struct Node: ::ShiftNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[3], results[1], Value(std::stoi(results[2])) };
	}

	Node(std::string out_, std::string in_, Value shiftAmount):
		::ShiftNode{ out_, in_, shiftAmount }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << in1 << " >> " << amount << std::endl;
		state[out] = state.find(in1)->second >> amount;
	}
};

}

struct BinaryNode: UnaryNode
{
	std::string in2;

	BinaryNode(std::string out_, std::string in1_, std::string in2_):
		UnaryNode{ out_, in1_ },
		in2{ in2_ }
	{}

	bool CanExecute(State const& state) const override
	{
		return UnaryNode::CanExecute(state) &&
			state.find(in2) != state.end();
	}
};

namespace And
{
std::regex Regex{ "([a-z]+) AND ([a-z]+) -> ([a-z]+)" };

struct Node: ::BinaryNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[3], results[1], results[2] };
	}

	Node(std::string out_, std::string in1_, std::string in2_):
		::BinaryNode{ out_, in1_, in2_ }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << in1 << " & " << in2 << std::endl;
		state[out] = state.find(in1)->second & state.find(in2)->second;
	}
};

}

namespace AndLiteral
{
std::regex Regex{ "(\\d+) AND ([a-z]+) -> ([a-z]+)" };

struct Node: ::UnaryNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[3], results[2], Value(std::stoi(results[1])) };
	}

	Value value;

	Node(std::string out_, std::string in1_, Value value_ ):
		::UnaryNode{ out_, in1_ },
		value{ value_ }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << value << " & " << in1 << std::endl;
		state[out] = state.find(in1)->second & value;
	}
};

}

namespace Or
{
std::regex Regex{ "([a-z]+) OR ([a-z]+) -> ([a-z]+)" };

struct Node: ::BinaryNode
{
	static ::Node* Parse(std::string const& input)
	{
		std::cmatch results;
		if (!std::regex_match(input.c_str(), results, Regex))
		{
			return nullptr;
		}

		return new Node{ results[3], results[1], results[2] };
	}

	Node(std::string out_, std::string in1_, std::string in2_):
		::BinaryNode{ out_, in1_, in2_ }
	{}

	void Execute(State& state) override
	{
		std::cout << out << " = " << in1 << " | " << in2 << std::endl;
		state[out] = state.find(in1)->second | state.find(in2)->second;
	}
};

}

Node*	MakeNode(std::string const& input)
{
	for (auto fn: {
		Assign::Node::Parse,
		AssignLiteral::Node::Parse,
		Not::Node::Parse,
		LeftShift::Node::Parse,
		RightShift::Node::Parse,
		And::Node::Parse,
		AndLiteral::Node::Parse,
		Or::Node::Parse,
	})
	{
		if (auto n = fn(input))
		{
			return n;
		}
	}
	std::cout << "Failed to parse: '" << input << "'" << std::endl;
	return nullptr;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::map<std::string, uint16_t>	wires;
	std::vector<std::unique_ptr<Node>> nodes;

	std::ifstream file(argv[1]);
	std::string line;
	while (std::getline(file, line))
	{
		if (auto p = MakeNode(line))
		{
			nodes.emplace_back(p);
		}
	}

	while (!nodes.empty())
	{
		for (auto i = nodes.begin(); i != nodes.end();)
		{
			if ((*i)->CanExecute(wires))
			{
				(*i)->Execute(wires);
				i = nodes.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	std::cout << wires["a"] << std::endl;

	return 0;
}
