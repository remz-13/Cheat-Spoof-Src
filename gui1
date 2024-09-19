using System;
using System.Drawing;
using System.Reflection.Emit;
using System.Windows.Forms;

// experimenting with guis (graphical user interfaces)
namespace ThunderPrivate
{
    public partial class Form1 : Form
    {
        private bool isAimbotOn = false;

        public Form1()
        {
            InitializeComponent();
            
            this.Text = "Thunder Private";
            this.BackColor = Color.FromArgb(44, 62, 80);
            this.ClientSize = new Size(600, 400);

            
            Button toggleButton = new Button();
            toggleButton.Text = "Turn Aimbot On";
            toggleButton.Font = new Font("Arial", 14, FontStyle.Bold);
            toggleButton.BackColor = Color.FromArgb(26, 188, 156);
            toggleButton.ForeColor = Color.White;
            toggleButton.FlatStyle = FlatStyle.Flat;
            toggleButton.Size = new Size(200, 50);
            toggleButton.Location = new Point((this.ClientSize.Width - toggleButton.Width) / 2, (this.ClientSize.Height - toggleButton.Height) / 2);
            toggleButton.Click += new EventHandler(ToggleButton_Click);
            this.Controls.Add(toggleButton);

           
            Label statusLabel = new Label();
            statusLabel.Text = "Aimbot is OFF";
            statusLabel.Font = new Font("Arial", 12, FontStyle.Regular);
            statusLabel.ForeColor = Color.White;
            statusLabel.Size = new Size(200, 50);
            statusLabel.TextAlign = ContentAlignment.MiddleCenter;
            statusLabel.Location = new Point((this.ClientSize.Width - statusLabel.Width) / 2, (this.ClientSize.Height - statusLabel.Height) / 2 + 70);
            this.Controls.Add(statusLabel);

            
            this.Tag = new Tuple<Button, Label>(toggleButton, statusLabel);
        }

        private void ToggleButton_Click(object sender, EventArgs e)
        {
            var controls = (Tuple<Button, Label>)this.Tag;
            Button toggleButton = controls.Item1;
            Label statusLabel = controls.Item2;

            isAimbotOn = !isAimbotOn;

            
            if (isAimbotOn)
            {
                toggleButton.Text = "Turn Aimbot Off";
                toggleButton.BackColor = Color.FromArgb(231, 76, 60);
                statusLabel.Text = "Aimbot is ON";
            }
            else
            {
                toggleButton.Text = "Turn Aimbot On";
                toggleButton.BackColor = Color.FromArgb(26, 188, 156);
                statusLabel.Text = "Aimbot is OFF";
            }
        }
    }
}
