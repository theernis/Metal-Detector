using System;
using System.Linq;
using System.Windows.Forms;
using System.IO.Ports;
using System.Timers;
using System.IO;

namespace Metal_Detector_WinForms
{
    public partial class Form1 : Form
    {
        // High-frequency timer (System.Timers.Timer) used for 10ms periodic work.
        private System.Timers.Timer periodicTimer;

        Serial serial;

        Preset preset;

        public Form1()
        {
            InitializeComponent();

            //initialize serial class
            serial = new Serial();
            serial.processSerialData = processSerialData;
            serial.listPorts(this);

            // Initialize the timer to fire every 1 ms.
            periodicTimer = new System.Timers.Timer(1);
            periodicTimer.AutoReset = true;
            periodicTimer.SynchronizingObject = this;
            periodicTimer.Elapsed += PeriodicTimer_Elapsed;
            periodicTimer.Start();

            // initialize checkboxes
            for (int i = 0; i <= 8; i++)
            {
                sensorPin1.Items.Add((i + 14).ToString());
                sensorPin2.Items.Add((i + 14).ToString());
                sensorPin3.Items.Add((i + 14).ToString());
                sensorPin4.Items.Add((i + 14).ToString());
                sensorPin5.Items.Add((i + 14).ToString());
                sensorPin6.Items.Add((i + 14).ToString());
            }

            initialize.Select();
            // loading default preset and loading presets from files to UI
            preset = new Preset();
            preset.loadPresetFromString(preset.defaultPreset, this);
            preset.loadPresetSaveList(this);
        }

        // Timer elapsed handler — executes every ~1 ms.
        private void PeriodicTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            serial.readSignal();
        }

        // processes received data
        private void processSerialData(byte[] data, int packetSize)
        {
            if (!serial.checkSerialDataIntegrity(data, packetSize))
            {
                return;
            }
            byte command = data[0];
            switch (command)
            {
                // display raw sensor data
                case 0x00:
                    {
                        int sensorCount = data[1];
                        int[] values = new int[sensorCount];
                        for (int i = 0; i < sensorCount; i++)
                        {
                            values[i] = (data[2 + i * 2] << 8) | data[3 + i * 2];
                        }
                        processSensorData(values, sensorCount);
                        break;
                    }
                // display measurements
                case 0x01:
                    {
                        double speed;
                        double length;
                        double width;
                        double angle;
                        speed = BitConverter.ToDouble(data, 1);
                        length = BitConverter.ToDouble(data, 9);
                        width = BitConverter.ToDouble(data, 17);
                        angle = BitConverter.ToDouble(data, 25);
                        displayMeasurements(DateTime.Now.ToString("hh:mm:ss tt"), (float)speed, (float)length, (float)width, (float)angle);
                        break;
                    }
                default:
                    break;
            }
            return;
        }

        // displays raw sensor data
        private void processSensorData(int[] values, int sensorCount)
        {
            string display = "Sensor data:";
            for (int i = 0; i < sensorCount; i++)
            {
                display += "\nSensor " + (i + 1).ToString() + ": " + (values[i] / 1023f).ToString("F3");
            }
            sensorData.Text = display;
            return;
        }

        // displays measured data
        private void displayMeasurements(string time, float speed, float length, float width, float angle)
        {
            string display = "Measurements:\n";
            display += "Time: " + time +"\n";
            display += "Speed: " + speed.ToString("F2") + " m/s\n";
            display += "Length: " + length.ToString("F2") + " m\n";
            display += "Width: " + width.ToString("F2") + " m\n";
            display += "Angle: " + angle.ToString("F2") + " °\n";
            measurements.Text = display;
        }

        // button handler for refreshing ports
        private void refreshPorts_Click(object sender, EventArgs e)
        {
            serial.listPorts(this);
        }

        // selecting serial port
        private void selectPort_Click(object sender, EventArgs e)
        {
            // error handling
            if (portList.SelectedIndex < 0 || portList.SelectedIndex >= portList.Items.Count)
            {
                serial.port = "";
                selectedPort.Text = "No Port Selected";
            }
            else
            {
                serial.port = portList.Text;
                selectedPort.Text = "Selected Port: " + serial.port;
            }
            if (serial.serialPort.IsOpen)
            {
                serial.serialPort.Close();
            }
            // selecting port
            if (SerialPort.GetPortNames().Contains(serial.port))
            {
                serial.serialPort.PortName = serial.port;
                
                serial.serialPort.Open();
                
                initialize.Select();
            }
            // more error handling
            else
            {
                MessageBox.Show("Connection problem");
                serial.listPorts(this);
            }
        }

        // initializing sensors
        private void initialize_Click(object sender, EventArgs e)
        {
            byte[] message;

            byte size;
            byte command = 0x00;
            byte sensorCount = 6;
            size = (byte)(2 + sensorCount);

            byte[] sensorPins = new byte[sensorCount];
            // error handling
            bool problem = false;
            if (sensorPin1.SelectedItem == null)
            {
                if (sensorPin1.Items.Contains(sensorPin1.Text.Trim()))
                {
                    sensorPin1.SelectedIndex = sensorPin1.Items.IndexOf(sensorPin1.Text.Trim());
                }
                else
                {
                    sensorPin1.ResetText();
                    sensorPin1.SelectedIndex = -1;
                    sensorPin1.Text = "error";
                    sensorPin1.Select();
                    problem = true;
                }
            }
            if (sensorPin2.SelectedItem == null)
            {
                if (sensorPin2.Items.Contains(sensorPin2.Text.Trim()))
                {
                    sensorPin2.SelectedIndex = sensorPin2.Items.IndexOf(sensorPin2.Text.Trim());
                }
                else
                {
                    sensorPin2.ResetText();
                    sensorPin2.SelectedIndex = -1;
                    sensorPin2.Text = "error";
                    sensorPin2.Select();
                    problem = true;
                }
            }
            if (sensorPin3.SelectedItem == null)
            {
                if (sensorPin3.Items.Contains(sensorPin3.Text.Trim()))
                {
                    sensorPin3.SelectedIndex = sensorPin3.Items.IndexOf(sensorPin3.Text.Trim());
                }
                else
                {
                    sensorPin3.ResetText();
                    sensorPin3.SelectedIndex = -1;
                    sensorPin3.Text = "error";
                    sensorPin3.Select();
                    problem = true;
                }
            }
            if (sensorPin4.SelectedItem == null)
            {
                if (sensorPin4.Items.Contains(sensorPin4.Text.Trim()))
                {
                    sensorPin4.SelectedIndex = sensorPin4.Items.IndexOf(sensorPin4.Text.Trim());
                }
                else
                {
                    sensorPin4.ResetText();
                    sensorPin4.SelectedIndex = -1;
                    sensorPin4.Text = "error";
                    sensorPin4.Select();
                    problem = true;
                }
            }
            if (sensorPin5.SelectedItem == null)
            {
                if (sensorPin5.Items.Contains(sensorPin5.Text.Trim()))
                {
                    sensorPin5.SelectedIndex = sensorPin5.Items.IndexOf(sensorPin5.Text.Trim());
                }
                else
                {
                    sensorPin5.ResetText();
                    sensorPin5.SelectedIndex = -1;
                    sensorPin5.Text = "error";
                    sensorPin5.Select();
                    problem = true;
                }
            }
            if (sensorPin6.SelectedItem == null)
            {
                if (sensorPin6.Items.Contains(sensorPin6.Text.Trim()))
                {
                    sensorPin6.SelectedIndex = sensorPin6.Items.IndexOf(sensorPin6.Text.Trim());
                }
                else
                {
                    sensorPin6.ResetText();
                    sensorPin6.SelectedIndex = -1;
                    sensorPin6.Text = "error";
                    sensorPin6.Select();
                    problem = true;
                }
            }
            if (problem)
            {
                MessageBox.Show("Error occured with sensor pins");
                return;
            }
            // setting pins
            sensorPins[0] = (byte)Int16.Parse(sensorPin1.SelectedItem.ToString());
            sensorPins[1] = (byte)Int16.Parse(sensorPin2.SelectedItem.ToString());
            sensorPins[2] = (byte)Int16.Parse(sensorPin3.SelectedItem.ToString());
            sensorPins[3] = (byte)Int16.Parse(sensorPin4.SelectedItem.ToString());
            sensorPins[4] = (byte)Int16.Parse(sensorPin5.SelectedItem.ToString());
            sensorPins[5] = (byte)Int16.Parse(sensorPin6.SelectedItem.ToString());

            // packet construct
            message = new byte[size];

            message[0] = command;
            message[1] = sensorCount;
            for (byte i = 0; i < sensorCount; i++)
            {
                message[2 + i] = sensorPins[i];
            }
            // send packet and initiate other data update packets
            serial.sendSignal(message, size, this);
            onTresholdChanged();
            onEnableChanged();
        }

        // send packet with new refresh rate
        private void refreshTime_ValueChanged(object sender, EventArgs e)
        {
            byte[] message;

            byte size = 2;
            byte command = 0x01;
            byte time = (byte)(refreshTime.Value * 100); // sending a value from 1 to 100 for 10ms to 1s

            message = new byte[size];
            message[0] = command;
            message[1] = time;

            serial.sendSignal(message, size, this);
        }

        // enable/disable raw data stream
        private void updateData_CheckedChanged(object sender, EventArgs e)
        {
            byte[] message;

            byte size = 2;
            byte command = 0x02;
            byte update = (byte)(updateData.Checked ? 1 : 0);

            message = new byte[size];
            message[0] = command;
            message[1] = update;

            serial.sendSignal(message, size, this);
        }

        // sending new treshold
        public void onTresholdChanged()
        {
            byte[] message;
            byte size = 14;
            byte command = 0x03;
            byte tresholdCount = 6;
            message = new byte[size];
            message[0] = command;
            message[1] = tresholdCount;

            message[2] = (byte)(((int)(treshold1.Value * 1023) >> 8) & 0xFF);
            message[3] = (byte)((int)(treshold1.Value * 1023) & 0xFF);
            message[4] = (byte)(((int)(treshold2.Value * 1023) >> 8) & 0xFF);
            message[5] = (byte)((int)(treshold2.Value * 1023) & 0xFF);
            message[6] = (byte)(((int)(treshold3.Value * 1023) >> 8) & 0xFF);
            message[7] = (byte)((int)(treshold3.Value * 1023) & 0xFF);
            message[8] = (byte)(((int)(treshold4.Value * 1023) >> 8) & 0xFF);
            message[9] = (byte)((int)(treshold4.Value * 1023) & 0xFF);
            message[10] = (byte)(((int)(treshold5.Value * 1023) >> 8) & 0xFF);
            message[11] = (byte)((int)(treshold5.Value * 1023) & 0xFF);
            message[12] = (byte)(((int)(treshold6.Value * 1023) >> 8) & 0xFF);
            message[13] = (byte)((int)(treshold6.Value * 1023) & 0xFF);

            serial.sendSignal(message, size, this);
        }

        // enable/disable sensors
        private void onEnableChanged()
        {
            byte[] message;
            byte size = 8;
            byte command = 0x04;
            byte sensorCount = 6;
            message = new byte[size];
            message[0] = command;
            message[1] = sensorCount;
            message[2] = (byte)(enable1.Checked ? 1 : 0);
            message[3] = (byte)(enable2.Checked ? 1 : 0);
            message[4] = (byte)(enable3.Checked ? 1 : 0);
            message[5] = (byte)(enable4.Checked ? 1 : 0);
            message[6] = (byte)(enable5.Checked ? 1 : 0);
            message[7] = (byte)(enable6.Checked ? 1 : 0);
            serial.sendSignal(message, size, this);
        }

        // send treshold and enable/disable packets to sensores
        private void update_Click(object sender, EventArgs e)
        {
            onTresholdChanged();
            onEnableChanged();
        }

        // load default settings when button is pressed
        private void loadDefaults_Click(object sender, EventArgs e)
        {
            preset.loadPresetFromString(preset.defaultPreset, this);
        }

        // save presets to files
        private void savePreset_Click(object sender, EventArgs e)
        {
            string newPreset = preset.generatePresetString(this);

            // Ensure presets directory exists so we can default the dialog there.
            Directory.CreateDirectory(preset.presetPath);

            using (SaveFileDialog dlg = new SaveFileDialog())
            {
                try
                {
                    dlg.InitialDirectory = Path.GetFullPath(preset.presetPath);
                }
                catch
                {
                    // Fall back silently if path resolution fails.
                }
                dlg.FileName = "preset" + (presetList.Items.Count + 1).ToString() + ".preset";
                dlg.Filter = "Preset files (*.preset)|*.preset|All files (*.*)|*.*";
                dlg.OverwritePrompt = true;

                if (dlg.ShowDialog() != DialogResult.OK)
                {
                    return;
                }

                string selectedFileName = Path.GetFileName(dlg.FileName);
                if (string.IsNullOrWhiteSpace(selectedFileName))
                {
                    MessageBox.Show("Invalid filename.");
                    return;
                }

                // Save into the presets folder regardless of where the dialog was pointed.
                string fullPath = Path.Combine(preset.presetPath, selectedFileName);
                File.WriteAllText(fullPath, newPreset);
                preset.loadPresetSaveList(this);
            }
        }

        // delete selected preset
        private void deletePreset_Click(object sender, EventArgs e)
        {
            if (presetList.SelectedItem == null)
            {
                MessageBox.Show("No preset Selected");
                return;
            }
            string presetName = presetList.SelectedItem.ToString();
            File.Delete(preset.presetPath + presetName);
            preset.loadPresetSaveList(this);
        }

        // preview selected preset
        private void previewPreset_Click(object sender, EventArgs e)
        {
            if (presetList.SelectedItem == null)
            {
                MessageBox.Show("No preset Selected");
                return;
            }
            string presetName = presetList.SelectedItem.ToString();
            MessageBox.Show(File.ReadAllText(preset.presetPath + presetName));
            loadPreset.Select();
        }

        // load selected preset
        private void loadPreset_Click(object sender, EventArgs e)
        {
            if (presetList.SelectedItem == null)
            {
                MessageBox.Show("No preset Selected");
                return;
            }
            string presetName = presetList.SelectedItem.ToString();
            preset.loadPresetFromString(File.ReadAllText(preset.presetPath + presetName), this);
        }
    }
}
// please don't make me program in C# ever again
// even though I don't like OOP, I can handle it
// what annoys me the most is memory safety of this language
// I hate not being in control of memory more than I hate debugging memory issues