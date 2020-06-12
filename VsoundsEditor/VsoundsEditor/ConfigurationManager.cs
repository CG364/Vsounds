using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace VsoundsEditor
{
    public class ConfigurationManager
    {
        public static List<SoundItem> GetSoundConfig()
        {
            if (!isCached)
            {
                string configFileText = System.IO.File.ReadAllText(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Vsounds", "config.json"));
                cache = JsonConvert.DeserializeObject<List<SoundItem>>(configFileText);
            }
            return cache;
        }
        public static void DropCache()
        {
            cache = null;
            isCached = false;
        }
        static bool isCached = false;
        static List<SoundItem> cache;
    }

    public class SoundItem 
    {
        public int inputType;
        public int inputActivation;
        public int inputActivationMod;
        public string Name;
        public string Path;
    }
}
