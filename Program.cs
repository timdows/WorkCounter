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
				//.UseUrls("http://192.168.1.172:5006")
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
