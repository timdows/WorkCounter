using Microsoft.EntityFrameworkCore;
using WorkCounter.Data.Models;

namespace WorkCounter.Data
{
	public class DataContext : DbContext
	{
		public DataContext(DbContextOptions options) : base(options)
		{
		}

		public DbSet<Device> Devices { get; set; }
		public DbSet<Pass> Passes { get; set; }
	}
}
