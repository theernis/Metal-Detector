using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Metal_Detector_WinForms
{
    internal class Preset
    {
        public string presetPath = "./presets/";
        public string defaultPreset = "";

        // initialize preset
        public Preset()
        {
            // create default preset
            defaultPreset += "sensorPin1:14\n";
            defaultPreset += "sensorPin2:15\n";
            defaultPreset += "sensorPin3:16\n";
            defaultPreset += "sensorPin4:17\n";
            defaultPreset += "sensorPin5:18\n";
            defaultPreset += "sensorPin6:19\n";
            defaultPreset += "refreshTime:0.10\n";
            defaultPreset += "updateData:true\n";
            defaultPreset += "treshold1:0.500\n";
            defaultPreset += "treshold2:0.500\n";
            defaultPreset += "treshold3:0.500\n";
            defaultPreset += "treshold4:0.500\n";
            defaultPreset += "treshold5:0.500\n";
            defaultPreset += "treshold6:0.500\n";
            defaultPreset += "enable1:true\n";
            defaultPreset += "enable2:true\n";
            defaultPreset += "enable3:true\n";
            defaultPreset += "enable4:true\n";
            defaultPreset += "enable5:true\n";
            defaultPreset += "enable6:true\n";
        }

        // load setting in the UI based on preset string
        public void loadPresetFromString(string preset, Form1 form)
        {
            // split by line and trim whitespace
            string[] settings = preset.Split('\n');
            for (int i = 0; i < settings.Length; i++)
            {
                settings[i] = settings[i].Trim();
            }
            // process each setting
            for (int i = 0; i < settings.Length; i++)
            {
                if (settings[i] == "")
                {
                    continue;
                }
                // split to setting and value
                string[] command = settings[i].Split(':');
                string setting = command[0];
                string value = command[1];
                switch (setting)
                {
                    case "sensorPin1":
                        if (form.sensorPin1.Items.Contains(value))
                        {
                            form.sensorPin1.SelectedIndex = form.sensorPin1.Items.IndexOf(value);
                        }
                        break;
                    case "sensorPin2":
                        if (form.sensorPin2.Items.Contains(value))
                        {
                            form.sensorPin2.SelectedIndex = form.sensorPin2.Items.IndexOf(value);
                        }
                        break;
                    case "sensorPin3":
                        if (form.sensorPin3.Items.Contains(value))
                        {
                            form.sensorPin3.SelectedIndex = form.sensorPin3.Items.IndexOf(value);
                        }
                        break;
                    case "sensorPin4":
                        if (form.sensorPin4.Items.Contains(value))
                        {
                            form.sensorPin4.SelectedIndex = form.sensorPin4.Items.IndexOf(value);
                        }
                        break;
                    case "sensorPin5":
                        if (form.sensorPin5.Items.Contains(value))
                        {
                            form.sensorPin5.SelectedIndex = form.sensorPin5.Items.IndexOf(value);
                        }
                        break;
                    case "sensorPin6":
                        if (form.sensorPin6.Items.Contains(value))
                        {
                            form.sensorPin6.SelectedIndex = form.sensorPin6.Items.IndexOf(value);
                        }
                        break;
                    case "refreshTime":
                        form.refreshTime.Value = decimal.Parse(value);
                        break;
                    case "updateData":
                        form.updateData.Checked = bool.Parse(value);
                        break;
                    case "treshold1":
                        form.treshold1.Value = decimal.Parse(value);
                        break;
                    case "treshold2":
                        form.treshold2.Value = decimal.Parse(value);
                        break;
                    case "treshold3":
                        form.treshold3.Value = decimal.Parse(value);
                        break;
                    case "treshold4":
                        form.treshold4.Value = decimal.Parse(value);
                        break;
                    case "treshold5":
                        form.treshold5.Value = decimal.Parse(value);
                        break;
                    case "treshold6":
                        form.treshold6.Value = decimal.Parse(value);
                        break;
                    case "enable1":
                        form.enable1.Checked = bool.Parse(value);
                        break;
                    case "enable2":
                        form.enable2.Checked = bool.Parse(value);
                        break;
                    case "enable3":
                        form.enable3.Checked = bool.Parse(value);
                        break;
                    case "enable4":
                        form.enable4.Checked = bool.Parse(value);
                        break;
                    case "enable5":
                        form.enable5.Checked = bool.Parse(value);
                        break;
                    case "enable6":
                        form.enable6.Checked = bool.Parse(value);
                        break;
                    default:
                        break;
                }
            }
            // reminder to initialize settings
            MessageBox.Show("Press 'Initialize' to apply changes");
            form.initialize.Select();
            return;
        }

        // generate preset from current settings
        public string generatePresetString(Form1 form)
        {
            string preset = "";
            preset += "sensorPin1:" + form.sensorPin1.SelectedItem.ToString() + "\n";
            preset += "sensorPin2:" + form.sensorPin2.SelectedItem.ToString() + "\n";
            preset += "sensorPin3:" + form.sensorPin3.SelectedItem.ToString() + "\n";
            preset += "sensorPin4:" + form.sensorPin4.SelectedItem.ToString() + "\n";
            preset += "sensorPin5:" + form.sensorPin5.SelectedItem.ToString() + "\n";
            preset += "sensorPin6:" + form.sensorPin6.SelectedItem.ToString() + "\n";
            preset += "refreshTime:" + form.refreshTime.Value.ToString("F2") + "\n";
            preset += "updateData:" + form.updateData.Checked.ToString() + "\n";
            preset += "treshold1:" + form.treshold1.Value.ToString("F3") + "\n";
            preset += "treshold2:" + form.treshold2.Value.ToString("F3") + "\n";
            preset += "treshold3:" + form.treshold3.Value.ToString("F3") + "\n";
            preset += "treshold4:" + form.treshold4.Value.ToString("F3") + "\n";
            preset += "treshold5:" + form.treshold5.Value.ToString("F3") + "\n";
            preset += "treshold6:" + form.treshold6.Value.ToString("F3") + "\n";
            preset += "enable1:" + form.enable1.Checked.ToString() + "\n";
            preset += "enable2:" + form.enable2.Checked.ToString() + "\n";
            preset += "enable3:" + form.enable3.Checked.ToString() + "\n";
            preset += "enable4:" + form.enable4.Checked.ToString() + "\n";
            preset += "enable5:" + form.enable5.Checked.ToString() + "\n";
            preset += "enable6:" + form.enable6.Checked.ToString() + "\n";
            return preset;
        }

        // load presets from preset files
        public void loadPresetSaveList(Form1 form)
        {
            form.presetList.ClearSelected();
            form.presetList.Items.Clear();
            if (Directory.Exists(presetPath))
            {
                string[] presets = Directory.GetFiles(presetPath);
                foreach (string preset in presets)
                {
                    form.presetList.Items.Add(Path.GetFileName(preset));
                }
            }
        }
    }
}
