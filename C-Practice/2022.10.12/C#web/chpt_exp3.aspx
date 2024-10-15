<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="chpt_exp3.aspx.cs" Inherits="chpt4_exp.chpt_exp3" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
    <style type="text/css">
        .auto-style1 {
            text-align: center;
        }
        .auto-style2 {
            height: 139px;
        }
        .auto-style3 {
            height: 124px;
        }
        .auto-style4 {
            height: 119px;
        }
        .auto-style5 {
            height: 119px;
            width: 806px;
        }
        .auto-style6 {
            height: 124px;
            width: 806px;
        }
        .auto-style7 {
            height: 139px;
            width: 806px;
        }
        .auto-style8 {
            width: 1734px;
        }
        .auto-style9 {
            text-align: left;
        }
        .auto-style10 {
            width: 1734px;
            text-align: left;
            height: 111px;
        }
        .auto-style11 {
            width: 100%;
        }
        .auto-style12 {
            height: 110px;
        }
        .auto-style13 {
            height: 111px;
        }
        .auto-style14 {
            height: 112px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="auto-style1" style="background-color: #33CCFF; font-size: x-large;">
            RadioButton测试1<table style="width:100%;">
                <tr>
                    <td class="auto-style5" style="font-size: x-large">sex:</td>
                    <td class="auto-style4">
                        <asp:RadioButton ID="RadioButton1" runat="server" Font-Size="X-Large" GroupName="g1" OnCheckedChanged="RadioButton1_CheckedChanged" Text="Male" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                        <asp:RadioButton ID="RadioButton2" runat="server" Font-Size="X-Large" GroupName="g1" Text="Female" />
                    </td>
                </tr>
                <tr>
                    <td class="auto-style6">Political Status:</td>
                    <td class="auto-style3">
                        <asp:RadioButtonList ID="RadioButtonList1" runat="server" RepeatColumns="3" Width="763px">
                            <asp:ListItem>Ordinary</asp:ListItem>
                            <asp:ListItem>Communist</asp:ListItem>
                            <asp:ListItem>Bourgeoisie</asp:ListItem>
                        </asp:RadioButtonList>
                    </td>
                </tr>
                <tr>
                    <td class="auto-style7">
                        <asp:Button ID="Button1" runat="server" Font-Size="X-Large" Height="65px" OnClick="Button1_Click" Text="Print" Width="191px" />
                    </td>
                    <td class="auto-style2">
                        <asp:Label ID="Label1" runat="server"></asp:Label>
                    </td>
                </tr>
            </table>
        </div>
        <div class="auto-style1" style="font-size: x-large; background-color: #00FF00">
            CheckBox测试2<br />
            <br />
            What are you interesed about?<br />
            <br />
            <asp:CheckBox ID="CheckBox1" runat="server" Text="Singing" />
&nbsp;&nbsp;
            <asp:CheckBox ID="CheckBox2" runat="server" Text="Dancing" />
&nbsp;&nbsp;
            <asp:CheckBox ID="CheckBox3" runat="server" Text="Rapping" />
&nbsp;&nbsp;
            <asp:CheckBox ID="CheckBox4" runat="server" Text="Playing basketball" />
            <br />
            <br />
            <br />
            I like listening 《Because you are so beautiful》<br />
            How about you?<br />
            <br />
            <asp:CheckBoxList ID="CheckBoxList1" runat="server" RepeatColumns="4" Width="1607px">
                <asp:ListItem>只因</asp:ListItem>
                <asp:ListItem>Pump It</asp:ListItem>
                <asp:ListItem>Never gonna give you up</asp:ListItem>
                <asp:ListItem>FA instrument</asp:ListItem>
            </asp:CheckBoxList>
            <br />
            <asp:Button ID="Button2" runat="server" Font-Size="X-Large" Height="59px" OnClick="Button2_Click" Text="Ascertain" Width="164px" />
            <br />
            <br />
            <asp:Label ID="Label2" runat="server" Font-Underline="False" ForeColor="Red"></asp:Label>
            <br />
        </div>
        <div class="auto-style1" style="background-color: #FFFF00; font-size: x-large; border-style: ridge">
            图片轮播测试3<br />
            <br />
            <asp:Image ID="Image1" runat="server" />
            <br />
            <asp:ImageButton ID="ImageButton1" runat="server" Height="50px" OnClick="ImageButton1_Click" Width="50px" />
&nbsp;
            <asp:ImageButton ID="ImageButton2" runat="server" Height="50px" OnClick="ImageButton2_Click" Width="50px" />
        </div>
        <div class="auto-style1" style="border-style: dotted; border-width: inherit; background-color: #000000; font-size: x-large; color: #FFFFFF">
            <div class="auto-style9">
                控件简历测试4<br />
                <br />
                Self-Resume</div>
            <table style="width:100%;">
                <tr>
                    <td class="auto-style10">First&amp;Last Name:<asp:TextBox ID="TextBox1" runat="server" Height="27px" Width="297px"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td class="auto-style8" style="border-spacing: 111px">
                        <div class="auto-style9" style="border-spacing: 111px">
                            <br />
                            Sex:&nbsp;
                            <asp:RadioButton ID="RadioButton3" runat="server" GroupName="s1" Text="Male" />
&nbsp;&nbsp;
                            <asp:RadioButton ID="RadioButton4" runat="server" GroupName="s1" Text="Female" />
&nbsp;&nbsp;
                            <asp:RadioButton ID="RadioButton5" runat="server" GroupName="s1" Text="Others" />
                            <br />
                            <table class="auto-style11">
                                <tr>
                                    <td class="auto-style12">Date of Birth:
                                        <asp:TextBox ID="TextBox2" runat="server" Height="27px" Width="331px"></asp:TextBox>
                                    </td>
                                </tr>
                                <tr>
                                    <td class="auto-style12">Major:
                                        <asp:DropDownList ID="DropDownList1" runat="server">
                                            <asp:ListItem>E-Commerce</asp:ListItem>
                                            <asp:ListItem>Data-base Management</asp:ListItem>
                                            <asp:ListItem>Artitecture</asp:ListItem>
                                            <asp:ListItem>Biology</asp:ListItem>
                                            <asp:ListItem>Commertial Analysis</asp:ListItem>
                                        </asp:DropDownList>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <table class="auto-style11">
                                            <tr>
                                                <td class="auto-style13">Hobbies:
                                                    <asp:CheckBoxList ID="CheckBoxList2" runat="server" Height="51px" RepeatColumns="4" Width="1544px">
                                                        <asp:ListItem>Eating watermelon</asp:ListItem>
                                                        <asp:ListItem>Van games</asp:ListItem>
                                                        <asp:ListItem>Taking exam 3</asp:ListItem>
                                                        <asp:ListItem>Sing&amp;Dance</asp:ListItem>
                                                    </asp:CheckBoxList>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td class="auto-style14">
                                                    <asp:Button ID="Button3" runat="server" Font-Size="X-Large" Height="72px" OnClick="Button3_Click" Text="Submit" Width="193px" />
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>
                                                    <asp:Label ID="Label3" runat="server" ForeColor="White"></asp:Label>
                                                    <br />
                                                    <br />
                                                    <br />
                                                    <br />
                                                    <br />
                                                </td>
                                            </tr>
                                        </table>
                                    </td>
                                </tr>
                            </table>
                        </div>
                    </td>
                </tr>
            </table>
        </div>
        <div class="auto-style1" style="font-size: x-large; border-style: groove">
            <br />
            文件上传测试4<br />
            <br />
            <asp:FileUpload ID="FileUpload1" runat="server" Height="56px" Width="566px" />
            <br />
            <asp:Button ID="Button4" runat="server" Font-Size="X-Large" Height="60px" OnClick="Button4_Click" Text="Upload" Width="159px" />
            <br />
            File Upload Status:<br />
            <br />
            <asp:Label ID="Label4" runat="server"></asp:Label>
        </div>
    </form>
</body>
</html>
