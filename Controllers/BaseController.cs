using Microsoft.AspNetCore.Mvc;
using WorkCounter.Data;

namespace WorkCounter.Controllers
{
	public class BaseController : Controller
    {
		public BaseController(DataContext dataContext)
		{
			_dataContext = dataContext;
		}

		protected DataContext _dataContext { get; set; }
	}
}
