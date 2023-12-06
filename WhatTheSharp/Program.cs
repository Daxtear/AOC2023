using System.Diagnostics.CodeAnalysis;

namespace WhatTheSharp {
	internal class Program {
		static void Main(string[] args) {
			Almanac al = new Almanac(File.ReadAllLines("Day5.txt"));
			var locs = al.Seeds.Select(seed => {
				return al.GetMapping(6, al.GetMapping(5, al.GetMapping(4, al.GetMapping(3, al.GetMapping(2, al.GetMapping(1, al.GetMapping(0, seed)))))));
				});
			Console.WriteLine(locs.Min());
		}
	}

	class Mapping {
		public long SourceRangeStart;
		public long SourceRangeEnd => SourceRangeStart + RangeLength - 1;
		public long DestRangeStart;
		public long DestRangeEnd => DestRangeStart + RangeLength - 1;
		public long RangeLength;

		public long GetDest(long input) {
			if(input < SourceRangeStart || input > SourceRangeEnd)
				return input;
			return input - SourceRangeStart + DestRangeStart;
		}

		public Mapping(string input) {
			string[] segments = input.Split(' ');
			SourceRangeStart = long.Parse(segments[1]);
			DestRangeStart = long.Parse(segments[0]);
			RangeLength = long.Parse(segments[2]);
		}
	}

	class Almanac {
		public List<long> Seeds = new List<long>();
		public List<Mapping>[] Mappings = new List<Mapping>[7];

		public long GetMapping(int level, long source) {
			var mapping = Mappings[level].LastOrDefault(t => t.SourceRangeStart <= source);
			if (mapping is null)
				return source;
			return mapping.GetDest(source);
		}

		public Almanac(string[] input) {
			int mode = 0;
			Mappings[mode] = new List<Mapping>();
			for (int a = 0; a < input.Length; ++a) {
				if(a == 0) {
					string[] seedstrings = input[a].Split(':')[1].Trim().Split(" ");
					foreach(string seed in seedstrings)
						Seeds.Add(long.Parse(seed));
					a += 2;
					continue;
				}
				if (string.IsNullOrEmpty(input[a])) {
					Mappings[mode] = Mappings[mode].OrderBy(t => t.SourceRangeStart).ToList();
					mode++;
					a++;
					Mappings[mode] = new List<Mapping>();
					continue;
				}
				Mapping m = new Mapping(input[a]);
				Mappings[mode].Add(m);
			}
		}
	}
}