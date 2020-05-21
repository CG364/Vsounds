using System;
using System.Collections.Generic;
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
    /// Interaction logic for AddItemPage1.xaml
    /// </summary>
    public partial class AddItemPage1 : UserControl
    {
        List<SoundItem> currentRegs;
        public event EventHandler<string> SoundNameChanged;
        public AddItemPage1()
        {
            InitializeComponent();
            currentRegs = ConfigurationManager.GetSoundConfig();
            nameAvailable.Visibility = Visibility.Hidden;
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            string t = nameTextBox.Text;
            bool valid = true;
            foreach (var item in currentRegs)
            {
                if (item.Name == t)
                {
                    valid = false;
                }
            }
            nameAvailable.Visibility = Visibility.Visible;
            if (valid)
            {
                nameAvailable.Text = "This name is available";
                nameAvailable.Foreground = Brushes.Lime;
                next_step.IsEnabled = true;
                try { SoundNameChanged.Invoke(this, t); } catch { Console.WriteLine("No EventHandler registered at SoundNameChanged"); }
            }
            else
            {
                nameAvailable.Text = "This name is not available";
                nameAvailable.Foreground = Brushes.Red;
                next_step.IsEnabled = false;
            }
        }
    }
}
