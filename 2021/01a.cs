using System;
using System.Linq;

class Program
{
	public static int Main(string[] args)
	{
		if (args.Length < 1)
		{
			Console.WriteLine("Specify file as 1st argument.");
			return 1;
		}

		uint last = (uint)1 << 31;
		uint result = (uint)System.IO.File.ReadLines(args[0]).Count(line => {
			uint sample = uint.Parse(line);
			bool res = sample > last;
			last = sample;
			return res;
		});

		Console.WriteLine(result);

		return 0;
	}
}
