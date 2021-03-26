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

            foreach(var attr in assembly.CustomAttributes)
            {
                Console.WriteLine("CustomAttribute: {0} {1}",
                    attr.AttributeType.FullName,
                    attr.ConstructorArguments.Aggregate("Args: ",
                    (string a, CustomAttributeTypedArgument e) => a + e.Value.ToString() + " " , a => a)
                    );
            }
        }


        public void ResolveScans()
        {

        }


        private List<IScan> scans;
    }
}
