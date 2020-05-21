using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace VsoundsEditor.AddItemSlides
{
    /// <summary>
    /// Interaction logic for AddItemPage2.xaml
    /// </summary>
    public partial class AddItemPage2 : UserControl
    {
        List<SoundItem> currentRegs;
        public event EventHandler<string> SoundFilePathChanged;
        public AddItemPage2()
        {
            InitializeComponent();
            currentRegs = ConfigurationManager.GetSoundConfig();
        }

        private void fileBrowse_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFD = new Microsoft.Win32.OpenFileDialog();
            openFD.Filter = "Sound files|*.mp3;*.ogg;*.flac;*.wav";
            openFD.ShowDialog();
            fileTb.Text = openFD.FileName;

        }

        private void fileTb_TextChanged(object sender, TextChangedEventArgs e)
        {
            bool valid = false; //more error checking coming...
            if (File.Exists(fileTb.Text))
            {
                valid = true;
            }

            if (valid)
            {
                fileOKTextBlock.Text = "File OK";
                next_step.IsEnabled = true;
                try { SoundFilePathChanged.Invoke(this, fileTb.Text); } catch { Console.WriteLine("No EventHandler registered at SoundFilePathChanged."); }
            }
            else
            {
                next_step.IsEnabled = false;
                fileOKTextBlock.Text = "Invalid file.";
            }
        }
    }
}
