using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WorkCounter.Data.Models
{
	public class SqlBase
	{
		[Key]
		public long ID { get; set; }

		//[Timestamp]
		//public byte[] Timestamp { get; set; }

		public DateTime? DateDeleted { get; set; }

		[NotMapped]
		public bool IsNew => ID == 0;

		[NotMapped]
		public bool IsDeleted => DateDeleted != null;
	}
}
