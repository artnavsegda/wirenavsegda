using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Microsoft.Maker.Serial;
using Microsoft.Maker.RemoteWiring;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace wirenavsegda
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        UsbSerial usb;
        RemoteDevice arduino;
        public MainPage()
        {
            this.InitializeComponent();

            usb = new UsbSerial("VID_2341", "PID_003D");   //I've written in my device D directly

            arduino = new RemoteDevice(usb);
            usb.ConnectionEstablished += OnConnectionEstablished;

            //SerialConfig.8N1 is the default config for Arduino devices over USB
            usb.begin(57600, SerialConfig.SERIAL_8N1);
        }
        private void OnConnectionEstablished()
        {
            //enable the buttons on the UI thread!
            var action = Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, new Windows.UI.Core.DispatchedHandler(() => {
                OnButton.IsEnabled = true;
                OffButton.IsEnabled = true;
            }));
        }
        private void OnButton_Click(object sender, RoutedEventArgs e)
        {
            //turn the LED connected to pin 13 ON
            arduino.digitalWrite(13, PinState.HIGH);
        }

        private void OffButton_Click(object sender, RoutedEventArgs e)
        {
            //turn the LED connected to pin 13 OFF
            arduino.digitalWrite(13, PinState.LOW);
        }
    }
}
