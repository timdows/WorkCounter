using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WorkCounter.Data;
using WorkCounter.Data.Models;

namespace WorkCounter.Controllers
{
	public class PassController : BaseController
	{
		private List<Device> _devices;

		public PassController(DataContext dataContext) : base(dataContext)
		{
			GetDevices();
		}

		public async Task<IActionResult> InsertValue([FromQuery]long deviceId, int distance, long millis)
		{
			var pass = new Pass
			{
				Distance = distance,
				Millis = millis,
				DateTimeAdded = DateTime.Now,
				Device = _devices.Single(a_item => a_item.ID == deviceId)
			};

			_dataContext.Passes.Add(pass);
			await _dataContext.SaveChangesAsync();

			return Json(true);
		}

		public async Task<IActionResult> AddDevice([FromQuery]string name)
		{
			var device = new Device
			{
				Name = name
			};

			_dataContext.Devices.Add(device);
			await _dataContext.SaveChangesAsync();

			GetDevices();

			return Json(device);
		}

		private void GetDevices()
		{
			_devices = _dataContext.Devices.ToList();
		}
	}
}
