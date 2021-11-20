using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reclaimer.Core
{
    public static class ServiceStore
    {
        private static Dictionary<Type, object> _services = new Dictionary<Type,object>();

        public static T GetService<T>(params object[] args)
        {
            object service;
            if (!_services.TryGetValue(typeof(T), out service))
                service = Activator.CreateInstance(typeof(T),args);
            return (T)service;
        }

        public static T TryGetService<T>() where T : class
        {
            object service;
            if (!_services.TryGetValue(typeof(T), out service))
                return null;
            return (T)service;
        }
    }
}
