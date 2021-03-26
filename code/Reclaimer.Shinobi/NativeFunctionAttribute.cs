using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reclaimer.Shinobi
{

    [AttributeUsage(AttributeTargets.Method)]
    public class NativeFunctionAttribute : NativeAddressAttribute
    {
    }
}
