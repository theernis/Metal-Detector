namespace Metal_Detector_WinForms
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.portList = new System.Windows.Forms.ComboBox();
            this.refreshPorts = new System.Windows.Forms.Button();
            this.selectPort = new System.Windows.Forms.Button();
            this.selectedPort = new System.Windows.Forms.Label();
            this.initialize = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.sensorPin1 = new System.Windows.Forms.ComboBox();
            this.sensorPin2 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.sensorPin3 = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.sensorPin4 = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.sensorPin5 = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.sensorPin6 = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.sensorData = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.refreshTime = new System.Windows.Forms.NumericUpDown();
            this.updateData = new System.Windows.Forms.CheckBox();
            this.measurements = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.treshold1 = new System.Windows.Forms.NumericUpDown();
            this.treshold2 = new System.Windows.Forms.NumericUpDown();
            this.treshold3 = new System.Windows.Forms.NumericUpDown();
            this.treshold4 = new System.Windows.Forms.NumericUpDown();
            this.treshold5 = new System.Windows.Forms.NumericUpDown();
            this.treshold6 = new System.Windows.Forms.NumericUpDown();
            this.enable1 = new System.Windows.Forms.CheckBox();
            this.enable2 = new System.Windows.Forms.CheckBox();
            this.enable3 = new System.Windows.Forms.CheckBox();
            this.enable6 = new System.Windows.Forms.CheckBox();
            this.enable5 = new System.Windows.Forms.CheckBox();
            this.enable4 = new System.Windows.Forms.CheckBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.update = new System.Windows.Forms.Button();
            this.presetList = new System.Windows.Forms.ListBox();
            this.loadDefaults = new System.Windows.Forms.Button();
            this.previewPreset = new System.Windows.Forms.Button();
            this.loadPreset = new System.Windows.Forms.Button();
            this.savePreset = new System.Windows.Forms.Button();
            this.deletePreset = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.refreshTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // portList
            // 
            this.portList.FormattingEnabled = true;
            this.portList.Location = new System.Drawing.Point(6, 21);
            this.portList.Name = "portList";
            this.portList.Size = new System.Drawing.Size(153, 24);
            this.portList.TabIndex = 0;
            // 
            // refreshPorts
            // 
            this.refreshPorts.Location = new System.Drawing.Point(6, 51);
            this.refreshPorts.Name = "refreshPorts";
            this.refreshPorts.Size = new System.Drawing.Size(153, 27);
            this.refreshPorts.TabIndex = 2;
            this.refreshPorts.Text = "Refresh ports";
            this.refreshPorts.UseVisualStyleBackColor = true;
            this.refreshPorts.Click += new System.EventHandler(this.refreshPorts_Click);
            // 
            // selectPort
            // 
            this.selectPort.Location = new System.Drawing.Point(6, 84);
            this.selectPort.Name = "selectPort";
            this.selectPort.Size = new System.Drawing.Size(153, 38);
            this.selectPort.TabIndex = 3;
            this.selectPort.Text = "Select";
            this.selectPort.UseVisualStyleBackColor = true;
            this.selectPort.Click += new System.EventHandler(this.selectPort_Click);
            // 
            // selectedPort
            // 
            this.selectedPort.AutoSize = true;
            this.selectedPort.Location = new System.Drawing.Point(6, 125);
            this.selectedPort.Name = "selectedPort";
            this.selectedPort.Size = new System.Drawing.Size(109, 16);
            this.selectedPort.TabIndex = 4;
            this.selectedPort.Text = "No Port Selected";
            // 
            // initialize
            // 
            this.initialize.Location = new System.Drawing.Point(6, 201);
            this.initialize.Name = "initialize";
            this.initialize.Size = new System.Drawing.Size(153, 34);
            this.initialize.TabIndex = 5;
            this.initialize.Text = "Initialize";
            this.initialize.UseVisualStyleBackColor = true;
            this.initialize.Click += new System.EventHandler(this.initialize_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Sensor 1 pin";
            // 
            // sensorPin1
            // 
            this.sensorPin1.FormattingEnabled = true;
            this.sensorPin1.Location = new System.Drawing.Point(93, 21);
            this.sensorPin1.Name = "sensorPin1";
            this.sensorPin1.Size = new System.Drawing.Size(66, 24);
            this.sensorPin1.TabIndex = 7;
            // 
            // sensorPin2
            // 
            this.sensorPin2.FormattingEnabled = true;
            this.sensorPin2.Location = new System.Drawing.Point(93, 51);
            this.sensorPin2.Name = "sensorPin2";
            this.sensorPin2.Size = new System.Drawing.Size(66, 24);
            this.sensorPin2.TabIndex = 9;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 54);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(81, 16);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sensor 2 pin";
            // 
            // sensorPin3
            // 
            this.sensorPin3.FormattingEnabled = true;
            this.sensorPin3.Location = new System.Drawing.Point(93, 81);
            this.sensorPin3.Name = "sensorPin3";
            this.sensorPin3.Size = new System.Drawing.Size(66, 24);
            this.sensorPin3.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 84);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 16);
            this.label4.TabIndex = 10;
            this.label4.Text = "Sensor 3 pin";
            // 
            // sensorPin4
            // 
            this.sensorPin4.FormattingEnabled = true;
            this.sensorPin4.Location = new System.Drawing.Point(93, 111);
            this.sensorPin4.Name = "sensorPin4";
            this.sensorPin4.Size = new System.Drawing.Size(66, 24);
            this.sensorPin4.TabIndex = 13;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 114);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(81, 16);
            this.label5.TabIndex = 12;
            this.label5.Text = "Sensor 4 pin";
            // 
            // sensorPin5
            // 
            this.sensorPin5.FormattingEnabled = true;
            this.sensorPin5.Location = new System.Drawing.Point(93, 141);
            this.sensorPin5.Name = "sensorPin5";
            this.sensorPin5.Size = new System.Drawing.Size(66, 24);
            this.sensorPin5.TabIndex = 15;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 144);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(81, 16);
            this.label6.TabIndex = 14;
            this.label6.Text = "Sensor 5 pin";
            // 
            // sensorPin6
            // 
            this.sensorPin6.FormattingEnabled = true;
            this.sensorPin6.Location = new System.Drawing.Point(93, 171);
            this.sensorPin6.Name = "sensorPin6";
            this.sensorPin6.Size = new System.Drawing.Size(66, 24);
            this.sensorPin6.TabIndex = 17;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 174);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(81, 16);
            this.label7.TabIndex = 16;
            this.label7.Text = "Sensor 6 pin";
            // 
            // sensorData
            // 
            this.sensorData.AutoSize = true;
            this.sensorData.Location = new System.Drawing.Point(6, 18);
            this.sensorData.Name = "sensorData";
            this.sensorData.Size = new System.Drawing.Size(97, 112);
            this.sensorData.TabIndex = 18;
            this.sensorData.Text = "Sensor data:\r\nSensor 1: 0.000\r\nSensor 2: 0.000\r\nSensor 3: 0.000\r\nSensor 4: 0.000\r" +
    "\nSensor 5: 0.000\r\nSensor 6: 0.000";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 243);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(85, 16);
            this.label8.TabIndex = 19;
            this.label8.Text = "Refresh time:";
            // 
            // refreshTime
            // 
            this.refreshTime.DecimalPlaces = 2;
            this.refreshTime.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.refreshTime.Location = new System.Drawing.Point(97, 241);
            this.refreshTime.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.refreshTime.Name = "refreshTime";
            this.refreshTime.Size = new System.Drawing.Size(62, 22);
            this.refreshTime.TabIndex = 20;
            this.refreshTime.Value = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.refreshTime.ValueChanged += new System.EventHandler(this.refreshTime_ValueChanged);
            // 
            // updateData
            // 
            this.updateData.AutoSize = true;
            this.updateData.Checked = true;
            this.updateData.CheckState = System.Windows.Forms.CheckState.Checked;
            this.updateData.Location = new System.Drawing.Point(6, 269);
            this.updateData.Name = "updateData";
            this.updateData.Size = new System.Drawing.Size(148, 20);
            this.updateData.TabIndex = 21;
            this.updateData.Text = "Update sensor data";
            this.updateData.UseVisualStyleBackColor = true;
            this.updateData.CheckedChanged += new System.EventHandler(this.updateData_CheckedChanged);
            // 
            // measurements
            // 
            this.measurements.AutoSize = true;
            this.measurements.Location = new System.Drawing.Point(6, 135);
            this.measurements.Name = "measurements";
            this.measurements.Size = new System.Drawing.Size(99, 96);
            this.measurements.TabIndex = 22;
            this.measurements.Text = "Measurements:\r\nTime: 00:00:00\r\nSpeed: NaN\r\nLength: NaN\r\nWidth: NaN\r\nAngle: NaN";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 18);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(114, 16);
            this.label9.TabIndex = 23;
            this.label9.Text = "Threshold values:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 198);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(81, 16);
            this.label10.TabIndex = 29;
            this.label10.Text = "Sensor 6 pin";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 168);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(81, 16);
            this.label11.TabIndex = 28;
            this.label11.Text = "Sensor 5 pin";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 138);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(81, 16);
            this.label12.TabIndex = 27;
            this.label12.Text = "Sensor 4 pin";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 108);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(81, 16);
            this.label13.TabIndex = 26;
            this.label13.Text = "Sensor 3 pin";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 78);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(81, 16);
            this.label14.TabIndex = 25;
            this.label14.Text = "Sensor 2 pin";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(6, 48);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(81, 16);
            this.label15.TabIndex = 24;
            this.label15.Text = "Sensor 1 pin";
            // 
            // treshold1
            // 
            this.treshold1.DecimalPlaces = 3;
            this.treshold1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold1.Location = new System.Drawing.Point(93, 46);
            this.treshold1.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold1.Name = "treshold1";
            this.treshold1.Size = new System.Drawing.Size(95, 22);
            this.treshold1.TabIndex = 30;
            this.treshold1.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // treshold2
            // 
            this.treshold2.DecimalPlaces = 3;
            this.treshold2.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold2.Location = new System.Drawing.Point(93, 76);
            this.treshold2.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold2.Name = "treshold2";
            this.treshold2.Size = new System.Drawing.Size(95, 22);
            this.treshold2.TabIndex = 31;
            this.treshold2.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // treshold3
            // 
            this.treshold3.DecimalPlaces = 3;
            this.treshold3.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold3.Location = new System.Drawing.Point(93, 106);
            this.treshold3.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold3.Name = "treshold3";
            this.treshold3.Size = new System.Drawing.Size(95, 22);
            this.treshold3.TabIndex = 32;
            this.treshold3.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // treshold4
            // 
            this.treshold4.DecimalPlaces = 3;
            this.treshold4.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold4.Location = new System.Drawing.Point(93, 139);
            this.treshold4.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold4.Name = "treshold4";
            this.treshold4.Size = new System.Drawing.Size(95, 22);
            this.treshold4.TabIndex = 33;
            this.treshold4.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // treshold5
            // 
            this.treshold5.DecimalPlaces = 3;
            this.treshold5.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold5.Location = new System.Drawing.Point(93, 166);
            this.treshold5.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold5.Name = "treshold5";
            this.treshold5.Size = new System.Drawing.Size(95, 22);
            this.treshold5.TabIndex = 34;
            this.treshold5.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // treshold6
            // 
            this.treshold6.DecimalPlaces = 3;
            this.treshold6.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.treshold6.Location = new System.Drawing.Point(93, 196);
            this.treshold6.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.treshold6.Name = "treshold6";
            this.treshold6.Size = new System.Drawing.Size(95, 22);
            this.treshold6.TabIndex = 35;
            this.treshold6.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // enable1
            // 
            this.enable1.AutoSize = true;
            this.enable1.Checked = true;
            this.enable1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable1.Location = new System.Drawing.Point(6, 241);
            this.enable1.Name = "enable1";
            this.enable1.Size = new System.Drawing.Size(126, 20);
            this.enable1.TabIndex = 36;
            this.enable1.Text = "Enable sensor 1";
            this.enable1.UseVisualStyleBackColor = true;
            // 
            // enable2
            // 
            this.enable2.AutoSize = true;
            this.enable2.Checked = true;
            this.enable2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable2.Location = new System.Drawing.Point(6, 267);
            this.enable2.Name = "enable2";
            this.enable2.Size = new System.Drawing.Size(126, 20);
            this.enable2.TabIndex = 37;
            this.enable2.Text = "Enable sensor 2";
            this.enable2.UseVisualStyleBackColor = true;
            // 
            // enable3
            // 
            this.enable3.AutoSize = true;
            this.enable3.Checked = true;
            this.enable3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable3.Location = new System.Drawing.Point(6, 293);
            this.enable3.Name = "enable3";
            this.enable3.Size = new System.Drawing.Size(126, 20);
            this.enable3.TabIndex = 38;
            this.enable3.Text = "Enable sensor 3";
            this.enable3.UseVisualStyleBackColor = true;
            // 
            // enable6
            // 
            this.enable6.AutoSize = true;
            this.enable6.Checked = true;
            this.enable6.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable6.Location = new System.Drawing.Point(6, 371);
            this.enable6.Name = "enable6";
            this.enable6.Size = new System.Drawing.Size(126, 20);
            this.enable6.TabIndex = 41;
            this.enable6.Text = "Enable sensor 6";
            this.enable6.UseVisualStyleBackColor = true;
            // 
            // enable5
            // 
            this.enable5.AutoSize = true;
            this.enable5.Checked = true;
            this.enable5.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable5.Location = new System.Drawing.Point(6, 345);
            this.enable5.Name = "enable5";
            this.enable5.Size = new System.Drawing.Size(126, 20);
            this.enable5.TabIndex = 40;
            this.enable5.Text = "Enable sensor 5";
            this.enable5.UseVisualStyleBackColor = true;
            // 
            // enable4
            // 
            this.enable4.AutoSize = true;
            this.enable4.Checked = true;
            this.enable4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.enable4.Location = new System.Drawing.Point(6, 319);
            this.enable4.Name = "enable4";
            this.enable4.Size = new System.Drawing.Size(126, 20);
            this.enable4.TabIndex = 39;
            this.enable4.Text = "Enable sensor 4";
            this.enable4.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Metal_Detector_WinForms.Properties.Resources.Image;
            this.pictureBox1.Location = new System.Drawing.Point(140, 21);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(174, 207);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 42;
            this.pictureBox1.TabStop = false;
            // 
            // update
            // 
            this.update.Location = new System.Drawing.Point(6, 422);
            this.update.Name = "update";
            this.update.Size = new System.Drawing.Size(179, 28);
            this.update.TabIndex = 43;
            this.update.Text = "Update properties";
            this.update.UseVisualStyleBackColor = true;
            this.update.Click += new System.EventHandler(this.update_Click);
            // 
            // presetList
            // 
            this.presetList.FormattingEnabled = true;
            this.presetList.ItemHeight = 16;
            this.presetList.Location = new System.Drawing.Point(6, 21);
            this.presetList.Name = "presetList";
            this.presetList.Size = new System.Drawing.Size(174, 180);
            this.presetList.Sorted = true;
            this.presetList.TabIndex = 44;
            // 
            // loadDefaults
            // 
            this.loadDefaults.Location = new System.Drawing.Point(198, 21);
            this.loadDefaults.Name = "loadDefaults";
            this.loadDefaults.Size = new System.Drawing.Size(116, 27);
            this.loadDefaults.TabIndex = 45;
            this.loadDefaults.Text = "Load defaults";
            this.loadDefaults.UseVisualStyleBackColor = true;
            this.loadDefaults.Click += new System.EventHandler(this.loadDefaults_Click);
            // 
            // previewPreset
            // 
            this.previewPreset.Location = new System.Drawing.Point(198, 54);
            this.previewPreset.Name = "previewPreset";
            this.previewPreset.Size = new System.Drawing.Size(116, 27);
            this.previewPreset.TabIndex = 46;
            this.previewPreset.Text = "Preview preset";
            this.previewPreset.UseVisualStyleBackColor = true;
            this.previewPreset.Click += new System.EventHandler(this.previewPreset_Click);
            // 
            // loadPreset
            // 
            this.loadPreset.Location = new System.Drawing.Point(198, 87);
            this.loadPreset.Name = "loadPreset";
            this.loadPreset.Size = new System.Drawing.Size(116, 27);
            this.loadPreset.TabIndex = 47;
            this.loadPreset.Text = "Load preset";
            this.loadPreset.UseVisualStyleBackColor = true;
            this.loadPreset.Click += new System.EventHandler(this.loadPreset_Click);
            // 
            // savePreset
            // 
            this.savePreset.Location = new System.Drawing.Point(198, 120);
            this.savePreset.Name = "savePreset";
            this.savePreset.Size = new System.Drawing.Size(116, 27);
            this.savePreset.TabIndex = 48;
            this.savePreset.Text = "Save preset";
            this.savePreset.UseVisualStyleBackColor = true;
            this.savePreset.Click += new System.EventHandler(this.savePreset_Click);
            // 
            // deletePreset
            // 
            this.deletePreset.Location = new System.Drawing.Point(198, 153);
            this.deletePreset.Name = "deletePreset";
            this.deletePreset.Size = new System.Drawing.Size(116, 27);
            this.deletePreset.TabIndex = 49;
            this.deletePreset.Text = "Delete preset";
            this.deletePreset.UseVisualStyleBackColor = true;
            this.deletePreset.Click += new System.EventHandler(this.deletePreset_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.portList);
            this.groupBox1.Controls.Add(this.refreshPorts);
            this.groupBox1.Controls.Add(this.selectPort);
            this.groupBox1.Controls.Add(this.selectedPort);
            this.groupBox1.Location = new System.Drawing.Point(17, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(170, 150);
            this.groupBox1.TabIndex = 50;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Select port";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.updateData);
            this.groupBox2.Controls.Add(this.refreshTime);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.sensorPin6);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.sensorPin5);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.sensorPin4);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.sensorPin3);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.sensorPin2);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.sensorPin1);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.initialize);
            this.groupBox2.Location = new System.Drawing.Point(17, 168);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(170, 300);
            this.groupBox2.TabIndex = 51;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Sensor pins";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.update);
            this.groupBox3.Controls.Add(this.enable6);
            this.groupBox3.Controls.Add(this.enable5);
            this.groupBox3.Controls.Add(this.enable4);
            this.groupBox3.Controls.Add(this.enable3);
            this.groupBox3.Controls.Add(this.enable2);
            this.groupBox3.Controls.Add(this.enable1);
            this.groupBox3.Controls.Add(this.treshold6);
            this.groupBox3.Controls.Add(this.treshold5);
            this.groupBox3.Controls.Add(this.treshold4);
            this.groupBox3.Controls.Add(this.treshold3);
            this.groupBox3.Controls.Add(this.treshold2);
            this.groupBox3.Controls.Add(this.treshold1);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label15);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Location = new System.Drawing.Point(193, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 456);
            this.groupBox3.TabIndex = 52;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Sensor properties";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.pictureBox1);
            this.groupBox4.Controls.Add(this.measurements);
            this.groupBox4.Controls.Add(this.sensorData);
            this.groupBox4.Location = new System.Drawing.Point(399, 12);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(320, 240);
            this.groupBox4.TabIndex = 53;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Sensor data";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.deletePreset);
            this.groupBox5.Controls.Add(this.savePreset);
            this.groupBox5.Controls.Add(this.loadPreset);
            this.groupBox5.Controls.Add(this.previewPreset);
            this.groupBox5.Controls.Add(this.loadDefaults);
            this.groupBox5.Controls.Add(this.presetList);
            this.groupBox5.Location = new System.Drawing.Point(399, 254);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(320, 214);
            this.groupBox5.TabIndex = 54;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Presets";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(732, 483);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.refreshTime)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treshold6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.ComboBox portList;
        public System.Windows.Forms.Button refreshPorts;
        public System.Windows.Forms.Button selectPort;
        public System.Windows.Forms.Label selectedPort;
        public System.Windows.Forms.Button initialize;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.ComboBox sensorPin1;
        public System.Windows.Forms.ComboBox sensorPin2;
        public System.Windows.Forms.Label label3;
        public System.Windows.Forms.ComboBox sensorPin3;
        public System.Windows.Forms.Label label4;
        public System.Windows.Forms.ComboBox sensorPin4;
        public System.Windows.Forms.Label label5;
        public System.Windows.Forms.ComboBox sensorPin5;
        public System.Windows.Forms.Label label6;
        public System.Windows.Forms.ComboBox sensorPin6;
        public System.Windows.Forms.Label label7;
        public System.Windows.Forms.Label sensorData;
        public System.Windows.Forms.Label label8;
        public System.Windows.Forms.NumericUpDown refreshTime;
        public System.Windows.Forms.CheckBox updateData;
        public System.Windows.Forms.Label measurements;
        public System.Windows.Forms.Label label9;
        public System.Windows.Forms.Label label10;
        public System.Windows.Forms.Label label11;
        public System.Windows.Forms.Label label12;
        public System.Windows.Forms.Label label13;
        public System.Windows.Forms.Label label14;
        public System.Windows.Forms.Label label15;
        public System.Windows.Forms.NumericUpDown treshold1;
        public System.Windows.Forms.NumericUpDown treshold2;
        public System.Windows.Forms.NumericUpDown treshold3;
        public System.Windows.Forms.NumericUpDown treshold4;
        public System.Windows.Forms.NumericUpDown treshold5;
        public System.Windows.Forms.NumericUpDown treshold6;
        public System.Windows.Forms.CheckBox enable1;
        public System.Windows.Forms.CheckBox enable2;
        public System.Windows.Forms.CheckBox enable3;
        public System.Windows.Forms.CheckBox enable6;
        public System.Windows.Forms.CheckBox enable5;
        public System.Windows.Forms.CheckBox enable4;
        public System.Windows.Forms.PictureBox pictureBox1;
        public System.Windows.Forms.Button update;
        public System.Windows.Forms.ListBox presetList;
        public System.Windows.Forms.Button loadDefaults;
        public System.Windows.Forms.Button previewPreset;
        public System.Windows.Forms.Button loadPreset;
        public System.Windows.Forms.Button savePreset;
        public System.Windows.Forms.Button deletePreset;
        public System.Windows.Forms.GroupBox groupBox1;
        public System.Windows.Forms.GroupBox groupBox2;
        public System.Windows.Forms.GroupBox groupBox3;
        public System.Windows.Forms.GroupBox groupBox4;
        public System.Windows.Forms.GroupBox groupBox5;
    }
}

