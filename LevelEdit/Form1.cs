using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace JojoGameEdit
{
    public partial class Form1 : Form
    {
        int levelw, levelh, tilesize;
        Brush[] tiles;
        Brush[] unchanged;
        Brush air = new SolidBrush(Color.FromArgb(255, 128, 204, 255));
        Brush block = new SolidBrush(Color.FromArgb(255, 0, 255, 0));
        bool draw = false;
        string title;
        string path = "";
        bool erase = false;

        public Form1()
        {
            levelw = 100;
            levelh = 50;
            tiles = new Brush[levelw * levelh];
            for (int i = 0; i < tiles.Length; i++) tiles[i] = air;
            unchanged = new Brush[levelw * levelh];
            for (int i = 0; i < unchanged.Length; i++) unchanged[i] = air;
            tilesize = 10;
            InitializeComponent();
            pictureBox1.Width = levelw * tilesize;
            pictureBox1.Height = levelh * tilesize;
            title = Text;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            About a = new About();
            a.ShowDialog();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            draw = true;
            if (e.Button == MouseButtons.Right) erase = true;
            if (e.Button == MouseButtons.Left) erase = false;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            draw = false;
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (draw)
            {
                int x = e.X / tilesize;
                int y = e.Y / tilesize;

                if (x + y * levelw < tiles.Length)
                {
                    if (erase) tiles[x + y * levelw] = air;
                    else tiles[x + y * levelw] = block;
                }
            }
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < tiles.Length; i++) e.Graphics.FillRectangle(tiles[i], i % levelw * tilesize, i / levelw * tilesize, tilesize, tilesize);
        }

        private void saveUnder()
        {
            readylabel.Text = "";
            SaveFileDialog saved = new SaveFileDialog();
            saved.Filter = "(*.png)|*.png";
            saved.ShowDialog();
            path = saved.FileName;
            save();
        }

        private void save()
        {
            readylabel.Text = "";
            if (path == "")
            {
                SaveFileDialog saved = new SaveFileDialog();
                saved.Filter = "(*.cpp)|*.cpp";
                saved.ShowDialog();
                path = saved.FileName;
            }
            List<Block> tilesNew = new List<Block>();
            for (int x = 0; x < levelw; x++)
            {
                for (int y = 0; y < levelh; y++)
                {
                    if(tiles[x + (levelh - y - 1) * levelw] != air) tilesNew.Add(new Block(x, y, 1));
                    //FLIP AND TESTFOR AIR
                }
            }
            StreamWriter s = null;
            try
            {
                s = new StreamWriter(path);
                for (int i = 0; i < tilesNew.Count; i++)
                {
                    s.WriteLine("Pixel(" + tilesNew[i].x + ", " + tilesNew[i].y + ", " + tilesNew[i].id + ");");
                }
                s.Close();
                readylabel.Text = "Gespeichert";
                for (int i = 0; i < tiles.Length; i++) unchanged[i] = tiles[i];
            }
            catch (IOException e)
            {
                readylabel.Text = "Fehler beim Speichern";
                if(s != null) s.Close();
            }
        }

        private void speichernToolStripMenuItem_Click(object sender, EventArgs e)
        {
            save();
        }

        private void öffnenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            readylabel.Text = "Bereit";
            if (isChanged())
            {
                DialogResult r = MessageBox.Show("Wollen Sie die Datei vor dem Beenden abspeichern?", "Speichern", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning);
                if (r == DialogResult.Cancel) return;
                if (r == DialogResult.Yes) save();
            }
            OpenFileDialog opend = new OpenFileDialog();
            opend.Filter = "(*.png)|*.png";
            opend.ShowDialog();
            string opath = opend.FileName;
            path = opath;
            Stream s = new FileStream(opath, FileMode.Open);
            Bitmap b = new Bitmap(s);
            s.Close();
            tiles = new Brush[b.Width * b.Height];
            unchanged = new Brush[b.Width * b.Height];
            for (int x = 0; x < b.Width; x++)
            {
                for (int y = 0; y < b.Height; y++)
                {
                    tiles[x + y * b.Width] = new SolidBrush(b.GetPixel(x, y));
                    unchanged[x + y * b.Width] = new SolidBrush(b.GetPixel(x, y));
                }
            }
            levelw = b.Width;
            levelh = b.Height;
            pictureBox1.Width = b.Width * tilesize;
            pictureBox1.Height = b.Height * tilesize;
            pictureBox1.Invalidate();
        }

        private void Updater_Tick(object sender, EventArgs e)
        {
            if (isChanged()) Text = title + "*";
            else Text = title;
            pictureBox1.Invalidate();
        }

        private bool isChanged()
        {
            for (int i = 0; i < tiles.Length; i++) if (tiles[i] != unchanged[i]) return true;
            return false;
        }

        private void speichernUnterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveUnder();
        }
    }

    class Block
    {
        public int x, y;
        public int id;

        public Block(int x, int y, int id)
        {
            this.x = x;
            this.y = y;
            this.id = id;
        }
    }
}
