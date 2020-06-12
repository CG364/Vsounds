using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting;
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
    /// Interaction logic for AddItemPage3.xaml
    /// </summary>
    public partial class AddItemPage3 : UserControl
    {
        List<SoundItem> currentRegs;
        public event EventHandler<int[]> KeyChanged;//first item = vk, second item = modifierKeys
        public event EventHandler Accepted;
        
        List<Key> CurrentlyHeldModKeys = new List<Key>();
        bool gotKey = false;
        bool buttonListenState = false;

        int acceptedModKey = -1;
        List<Key> acceptedModKeyArray;
        int acceptedvk = -1;
        Button btn;
        public AddItemPage3()
        {
            InitializeComponent();
            btn = next_step;
            currentRegs = ConfigurationManager.GetSoundConfig();
        }

        private void keyListen_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            
        }

        private void KeyTb_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (!gotKey)
            {
                KeyTb.Text = "No keypress detected.";
            }
        }

        private void keyListen_KeyDown(object sender, KeyEventArgs e)
        {
            if (buttonListenState)
                switch (e.Key)
                {
                    case Key.LeftShift:
                    case Key.RightShift:
                    case Key.RightCtrl:
                    case Key.LeftCtrl:
                    case Key.RightAlt:
                    case Key.LeftAlt:
                        CurrentlyHeldModKeys.Add(e.Key);
                        break;
                    default:
                        if (CurrentlyHeldModKeys.Count != 0)
                        {
                            //ladies and gentlemen, we got him
                            gotKey = true;
                            acceptedModKey = getModKeysFromKeyArray(CurrentlyHeldModKeys);
                            acceptedModKeyArray = new List<Key>(CurrentlyHeldModKeys);
                            CurrentlyHeldModKeys.Clear();
                            acceptedvk = KeyInterop.VirtualKeyFromKey(e.Key);
                            KeyTb.Text = "";
                            foreach (var item in acceptedModKeyArray)
                            {
                                KeyTb.Text += item.ToString() + " + ";
                            }
                            KeyTb.Text += e.Key.ToString();
                        }
                        break;
                }
        }

        private void keyListen_KeyUp(object sender, KeyEventArgs e)
        {
            if(buttonListenState)
                switch (e.Key)
                {
                    case Key.LeftShift:
                    case Key.RightShift:
                    case Key.RightAlt:
                    case Key.LeftAlt:
                    case Key.RightCtrl:
                    case Key.LeftCtrl:
                        CurrentlyHeldModKeys.Remove(e.Key);
                        CurrentlyHeldModKeys = CurrentlyHeldModKeys.Distinct().ToList();
                        break;
                    default:
                        break;
                }
        }

        private void keyListen_Click(object sender, RoutedEventArgs e)
        {
            buttonListenState = !buttonListenState;
            if (buttonListenState)
            {
                KeyTb.Text = "Listening...";
                buttonIcon.Kind = MaterialDesignThemes.Wpf.PackIconKind.Stop;
            }
            else
            {
                buttonIcon.Kind = MaterialDesignThemes.Wpf.PackIconKind.Keyboard;
                if (!gotKey)
                {
                    KeyTb.Text = "No key found";
                }
            }
        }

        private void keyListen_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (buttonListenState)
            {
                keyListen.Focus();
            }
        }

        int getModKeysFromKeyArray(List<Key> inList)
        {
            int output = 0;
            foreach (var item in inList)
            {
                switch (item)
                {
                    case Key.LeftCtrl:
                    case Key.RightCtrl:
                        output = output | 0x0002; // ctrl win32 keycode
                        break;

                    case Key.LeftAlt:
                    case Key.RightAlt:
                        output = output | 0x0001; // alt win32 keycode
                        break;

                    case Key.LeftShift:
                    case Key.RightShift:
                        output = output | 0x0004; // shift win32 keycode
                        break;
                    default:
                        break;
                }
            }
            output = output | 0x4000; //mod_norepeat keycode
            return output;
        }

        private void next_step_Click(object sender, RoutedEventArgs e)
        {
            if (Accepted != null)
            {
                Accepted.Invoke(this, null);
            }
                
        }
    }
}
