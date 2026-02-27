using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace Metal_Detector_WinForms
{
    internal class Serial
    {
        public string port = "";
        public SerialPort serialPort;

        public Action<byte[], int> processSerialData = null;

        // initialize serial class
        public Serial()
        {
            serialPort = new SerialPort();
            serialPort.BaudRate = 9600;
        }

        // lists available ports
        public void listPorts(Form1 form)
        {
            form.portList.Items.Clear();
            form.portList.Text = "";
            string[] ports = SerialPort.GetPortNames();
            form.portList.Items.AddRange(ports);
            // select first port
            if (form.portList.Items.Count > 0)
            {
                form.portList.SelectedIndex = 0;
            }
            // select previously selected port if possible
            if (form.portList.Items.Contains(port))
            {
                form.portList.SelectedItem = port;
            }
        }

        // construct and send a packet
        // I hate that I must send a Button object, creating a public variable in a class doesn't work
        public void sendSignal(byte[] data, byte size, Form1 form)
        {
            byte[] signal = new byte[2 + size + 2];
            byte sum = size;
            byte parity = size;

            signal[0] = 0xff;
            signal[1] = size;

            for (int i = 0; i < size; i++)
            {
                signal[2 + i] = data[i];
                sum += data[i];
                parity ^= data[i];
            }
            signal[size + 2] = sum;
            signal[size + 3] = parity;

            if (serialPort.IsOpen && port != "")
            {
                serialPort.Write(signal, 0, signal.Length);
            }
            else
            {
                MessageBox.Show("Serial port is not open.");
                form.selectPort.Select();
            }
        }

        // checks received packet integrity
        public bool checkSerialDataIntegrity(byte[] data, int packetSize)
        {
            int dataSize = packetSize - 2;
            byte sum = (byte)dataSize;
            byte parity = (byte)dataSize;
            // calculates sum and parity bytes
            for (int i = 0; i < dataSize; i++)
            {
                sum += data[i];
                parity ^= data[i];
            }
            // compares them to received ones
            return (sum == data[packetSize - 2] && parity == data[packetSize - 1]);
        }

        // needed static variables, but they dont work like c++, so I did this
        bool reading = false;
        byte[] buffer = null;
        int bufferSize = 0;
        int bytesRead = 0;
        // read serial data
        public void readSignal()
        {
            if (!serialPort.IsOpen)
            {
                return;
            }
            // read packets, 5 at most
            int packetCounter = 0;
            while (serialPort.BytesToRead > 0 && packetCounter < 5)
            {
                // look for start byte
                if (!reading && serialPort.ReadByte() == 0xFF)
                {
                    reading = true;
                    bufferSize = serialPort.ReadByte() + 2; // including checksum and parity
                    buffer = new byte[bufferSize];
                    bytesRead = 0;
                }
                // read packet if start byte is found
                else if (reading)
                {
                    buffer[bytesRead] = (byte)serialPort.ReadByte();
                    bytesRead++;
                    // process data if packet finished reading
                    if (bytesRead >= bufferSize)
                    {
                        processSerialData(buffer, bufferSize);
                        buffer = null;
                        reading = false;
                        packetCounter++;
                    }
                }
            }
        }
    }
}
