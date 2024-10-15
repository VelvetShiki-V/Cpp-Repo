using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace chpt4_exp
{
    public partial class chpt_exp3 : System.Web.UI.Page
    {
        static int j = 1;
        string[] p = {
            ""
                ,
            "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fdingyue.ws.126.net%2F1IEL8RNHM5JaMP5G%3DGXu85%3Dk9MwF6WGvUMYxch88HuNyQ1555318677917.gif&refer=http%3A%2F%2Fdingyue.ws.126.net&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1668134870&t=d0966dc5c1b4a7dc980af411e95c3974"
                ,
            "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fc-ssl.duitang.com%2Fuploads%2Fitem%2F201807%2F13%2F20180713114316_mkkoe.thumb.400_0.gif&refer=http%3A%2F%2Fc-ssl.duitang.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1668135721&t=73b7b857147e11d48e7d6091c07ae860"
                ,
            "https://pic.rmb.bdstatic.com/3b1c2286923d375797a5f1a5884bda5c1510.gif"
                ,
            "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fp6-sign.bdxiguaimg.com%2Ftos-cn-i-0022%2F089841af9a594f3e8948e7b7f293367a~640x0.image%3Fx-expires%3D1661939893%26x-signature%3D7XsHTu1qimwhBjp%252BWo6ZKC9jvLI%253D&refer=http%3A%2F%2Fp6-sign.bdxiguaimg.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1668135786&t=77bf0e709f4440a45d976685d6376f5d"
        };
        protected void Page_Load(object sender, EventArgs e)
        {
            Image1.ImageUrl = p[j];
            if(j == 1) ImageButton1.Enabled = false;
            if(j == 4) ImageButton2.Enabled = false;
            ImageButton1.ImageUrl = "https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fbpic.51yuansu.com%2Fpic2%2Fcover%2F00%2F42%2F46%2F58138dd06203c_610.jpg&refer=http%3A%2F%2Fbpic.51yuansu.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1668135143&t=9385ec0e2a28d757f626517a233d9fbd";
            ImageButton2.ImageUrl = "https://img1.baidu.com/it/u=1247767187,4063489291&fm=253&fmt=auto&app=138&f=JPEG?w=500&h=500";
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            string sex;
            if (RadioButton1.Checked) sex = RadioButton1.Text;
            else sex = RadioButton2.Text;
            Label1.Text = "You, a " + sex + ", are a " + RadioButtonList1.Text + ".";
        }

        protected void RadioButton1_CheckedChanged(object sender, EventArgs e)
        {
            ;
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            string basketball = "";     // 爱好字符串
            if (CheckBox1.Checked) basketball += CheckBox1.Text + "&nbsp&nbsp|&nbsp&nbsp";
            if (CheckBox2.Checked) basketball += CheckBox2.Text + "&nbsp&nbsp|&nbsp&nbsp";
            if (CheckBox3.Checked) basketball += CheckBox3.Text + "&nbsp&nbsp|&nbsp&nbsp";
            if (CheckBox4.Checked) basketball += CheckBox4.Text + "&nbsp&nbsp|&nbsp&nbsp";
            if (basketball == "") Label2.Text += "You really like NOTHING!!";
            else Label2.Text = "You always do " + "<br>" + basketball;
            Label2.Text += "<br><br>";
            string music = "";      // 音乐字符串
            for(int i = 0; i < CheckBoxList1.Items.Count; ++i)
            {
                if (CheckBoxList1.Items[i].Selected)
                    music += CheckBoxList1.Items[i].Text + "&nbsp&nbsp|&nbsp&nbsp";
            }
            if (music == "") Label2.Text += "You are a music DUMB!!";
            else Label2.Text += "These are songs you often hear and dance: " + "<br><br>" + music + "<br>";
        }

        protected void ImageButton1_Click(object sender, ImageClickEventArgs e)
        {
            j -= 1;
            Image1.ImageUrl = p[j];
            if (j == 1)
            {
                ImageButton1.Enabled = false;
                ImageButton2.Enabled = true;
            }
            else
            {
                ImageButton1.Enabled = true;
                ImageButton2.Enabled = true;
            }
        }

        protected void ImageButton2_Click(object sender, ImageClickEventArgs e)
        {
            j += 1;
            Image1.ImageUrl = p[j];
            if (j == 4)
            {
                ImageButton2.Enabled = false;
                ImageButton1.Enabled = true;
            }
            else
            {
                ImageButton2.Enabled = true;
                ImageButton1.Enabled = true;
            }

        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            string resume = "Your info is presented below : " + "<br>";
            resume += "Name: " + TextBox1.Text + "<br>";
            if(RadioButton3.Checked) resume += "Sex: " + RadioButton3.Text + "<br>";
            else if (RadioButton4.Checked) resume += "Sex: " + RadioButton4.Text + "<br>";
            else resume += "Sex: " + RadioButton5.Text + "<br>";
            resume += "Your birthday is : " + TextBox2.Text + "<br>";
            resume += "Your major is: " + DropDownList1.Text + "<br>";
            resume += "What you interested about is: " + "<br>";
            for(int i = 0; i < CheckBoxList2.Items.Count; i++)
            {
                if (CheckBoxList2.Items[i].Selected)
                {
                    resume += CheckBoxList2.Items[i].Text + "&nbsp&nbsp|&nbsp&nbsp";
                }
            }
            Label3.Text = resume;
        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            string path = "";
            if (FileUpload1.HasFile == true)
            {
                FileUpload1.SaveAs(Server.MapPath("./my_uploaded_files/") + FileUpload1.FileName);
                path += "File uploaded successfully!" + "<br><br>";
                path += "File Name:  " + FileUpload1.PostedFile.FileName + "<br><br>";
                path += "File Size:  " + FileUpload1.PostedFile.ContentLength + " bytes" + "<br><br>";
                path += "File Type:  " + FileUpload1.PostedFile.ContentType + "<br>";
            }
            else path += "File is not selected, please click the button above to retry!" + "<br>";
            Label4.Text = path;
        }
    }
}