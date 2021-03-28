using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Loader;
using System.Reflection;

namespace Reclaimer.Shinobi.Internal
{

    public class ScanManager
    {

        public void CollectScans(Assembly assembly = null)
        {
            if (assembly == null)
            {
                assembly = Assembly.GetCallingAssembly();
            }

            foreach(var attr in assembly.DefinedTypes)
            {
            }
        }


        public void ResolveScans()
        {

        }


        private List<IScan> scans;
    }
}
