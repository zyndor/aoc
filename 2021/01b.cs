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

		uint max = (uint)1 << 31;
		uint[] samples = { max, max, max, max };
		uint result = (uint)System.IO.File.ReadLines(args[0]).Count(line => {
			for (int i = 0; i < samples.Length - 1; ++i)
			{
				samples[i] = samples[i + 1];
			}

			samples[3] = uint.Parse(line);

			return samples[3] > samples[0];
		});

		Console.WriteLine(result);

		return 0;
	}
}
