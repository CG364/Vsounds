using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using System.Windows.Shapes;

namespace VsoundsEditor.AddItemSlides
{
    /// <summary>
    /// Interaction logic for AddItemMainWindow.xaml
    /// </summary>
    public partial class AddItemMainWindow : Window
    {
        SoundItem newItem = new SoundItem();
        public AddItemMainWindow()
        {
            InitializeComponent();
            namePage.SoundNameChanged += NamePage_SoundNameChanged;
            pathPage.SoundFilePathChanged += PathPage_SoundFilePathChanged;
            keyPage.KeyChanged += KeyPage_KeyChanged;
            keyPage.Accepted += KeyPage_Accepted;
            newItem.inputType = 1; //always keyboard
        }

        private void KeyPage_Accepted(object sender, EventArgs e)
        {
            Debugger.Break();
        }

        private void KeyPage_KeyChanged(object sender, int[] e)
        {
            newItem.inputActivationMod = e[1];
            newItem.inputActivation = e[0];
        }

        private void PathPage_SoundFilePathChanged(object sender, string e)
        {
            newItem.Path = e;
        }

        private void NamePage_SoundNameChanged(object sender, string e)
        {
            newItem.Name = e;
        }

    }
}
