using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static WhatTheSharp.NicksSolutions;

namespace WhatTheSharp {
	public static class NicksSolutions {

		public static void Day7_2() {
			var lines = File.ReadLines("Day7.txt").ToList();

			List<Hand2> values = new List<Hand2>();

			foreach (var line in lines) {
				var cards = line.Split(" ").First();
				var bid = int.Parse(line.Split(" ").Last());

				values.Add(new Hand2(cards, bid));
			}

			values = values.OrderBy(x => x.strength).ThenBy(x => x.value).ToList();

			int sum = 0;

			for (int i = 0; i < values.Count; i++) {
				Console.WriteLine(values[i]);
				sum += (i + 1) * values[i].bid;
			}

			Console.WriteLine(sum);
		}

		public class Hand2{
			public string cards;
			public int bid;
			public int strength;
			public int value;
			public Hand2(string cards, int bid) {
				this.cards = cards;
				this.bid = bid;

				int jokers = cards.Count(x => x == 'J');

				foreach (var card in cards.Replace("J", "")) {
					int count = cards.Count(x => x == card);

					switch (count) {
						case 5:
							if (this.strength < 6) { this.strength = 6; }
							break;

						case 4:
							if (this.strength < 5) { this.strength = 5; }
							break;

						case 3:
							if (this.strength == 1 || this.strength == -1) { this.strength = 4; }
							else if (this.strength < 3) { this.strength = 3; }
							break;

						case 2:
							switch (this.strength) {
								case 3:
									this.strength = 4; break;
								case 1:
									this.strength = 2; break;
								case 0:
									this.strength = -1; break;
								case -1:
									this.strength = 1; break;
							}
							break;
					}
				}
				if (jokers > 0) {
					switch (this.strength) {
						case 5:
							this.strength = 6; break;
						case 3:
							this.strength += 1 + jokers; break;
						case 2:
							this.strength = 4; break;
						case 1:
							if (jokers == 1) { this.strength = 3; }
							else { this.strength += 2 + jokers; }
							break;
						case 0:
							switch (jokers) {
								case 5:
									this.strength = 6; break;
								case 4:
									this.strength = 6; break;
								case 3:
									this.strength = 5; break;
								case 2:
									this.strength = 3; break;
								case 1:
									this.strength = 1; break;
							}
							break;
					}
				}

				var temp = cards.Replace('A', 'E');
				temp = temp.Replace('K', 'D');
				temp = temp.Replace('Q', 'C');
				temp = temp.Replace('J', '1');
				temp = temp.Replace('T', 'A');

				this.value = Convert.ToInt32(temp, 16);
			}

			public override string ToString() {
				return cards + " " + strength;
			}
		}
	}
}
