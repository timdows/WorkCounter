using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using System.IO;

namespace WorkCounter
{
	public class Program
    {
        public static void Main(string[] args)
        {
            var host = new WebHostBuilder()
				.UseUrls("http://localhost:5006")
                .UseKestrel()
                .UseContentRoot(Directory.GetCurrentDirectory())
                .UseIISIntegration()
                .UseStartup<Startup>()
                .Build();

            host.Run();
        }
    }
}
