using System;

namespace WorkCounter.Data.Models
{
	public class Pass : SqlBase
    {
		public Device Device { get; set; }
		public int Distance { get; set; }
		public DateTime DateTimeAdded { get; set; }
		public long Millis { get; set; }
	}
}
