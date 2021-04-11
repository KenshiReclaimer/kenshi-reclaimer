using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Loader;
using System.Reflection;

namespace Reclaimer.Shinobi.Internal
{
    static internal class AssemblyExt
    {
        public static IEnumerable<Type> GetLoadableTypes(this Assembly assembly)
        {
            if (assembly == null) throw new ArgumentNullException(nameof(assembly));
            try
            {
                return assembly.GetTypes();
            }
            catch (ReflectionTypeLoadException e)
            {
                return e.Types.Where(t => t != null);
            }
        }
    }
    public class ScanManager
    {

        public void CollectScans(Assembly assembly = null)
        {
            if (assembly == null)
            {
                assembly = Assembly.GetCallingAssembly();
            }

            Console.WriteLine("Assembly: {0}", assembly.FullName);

            foreach(var types in AssemblyExt.GetLoadableTypes(assembly))
            {
                Console.WriteLine("\t> {0}", types.FullName);
                foreach(var attr in types.CustomAttributes)
                {
                    Console.WriteLine("\t\t> {0}", attr.ToString());
                }
            }
        }

        public void ResolveScans()
        {

        }


        private List<IScan> scans;
    }
}
