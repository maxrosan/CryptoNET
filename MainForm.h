#pragma once
#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include "VirtualDisk.h"
#include "Cipher.h"
#include "DatabaseHandler.h"
#include "DatabaseRAMHandler.h"

namespace CryptoNET {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Sumário para MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm()
		{
			this->cipher = nullptr;

			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBoxPass;
	protected:

	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ComboBox^ comboBoxAlgo;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ comboBoxLetter;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownSize;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::Button^ button17;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxPassDec;

	private: System::Windows::Forms::Button^ button18;
	private: System::Windows::Forms::Button^ button19;




	private: Cipher^ cipher;
	public:
		void setCipher(Cipher ^cipher) {
			this->cipher = cipher;
		}

		void loadInformation() {
			if (this->cipher == nullptr) {
				return;
			}
			if (this->cipher->areLibrariesLoaded()) {
				this->toolStripStatusLabel1->Text = "The DLLs are loaded!";
			}
			else {
				this->toolStripStatusLabel1->Text = "Failed to load the DLLs!";
			}
		}
	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBoxPass = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->comboBoxAlgo = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownSize = (gcnew System::Windows::Forms::NumericUpDown());
			this->comboBoxLetter = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxPassDec = (gcnew System::Windows::Forms::TextBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSize))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// textBoxPass
			// 
			this->textBoxPass->Location = System::Drawing::Point(32, 28);
			this->textBoxPass->MaxLength = 16;
			this->textBoxPass->Name = L"textBoxPass";
			this->textBoxPass->Size = System::Drawing::Size(259, 22);
			this->textBoxPass->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(302, 26);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(139, 27);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Open decrypted text";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Password (16 chars)";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 472);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(636, 26);
			this->statusStrip1->TabIndex = 3;
			this->statusStrip1->Text = L"statusStrip1";
			this->statusStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainForm::statusStrip1_ItemClicked);
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(151, 20);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Click += gcnew System::EventHandler(this, &MainForm::toolStripStatusLabel1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(6, 6);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(521, 271);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(302, 79);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(189, 27);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Encrypt text and save file";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(443, 26);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(142, 27);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Open encrypted text";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// comboBoxAlgo
			// 
			this->comboBoxAlgo->FormattingEnabled = true;
			this->comboBoxAlgo->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"AES256" });
			this->comboBoxAlgo->Location = System::Drawing::Point(32, 81);
			this->comboBoxAlgo->Name = L"comboBoxAlgo";
			this->comboBoxAlgo->Size = System::Drawing::Size(259, 24);
			this->comboBoxAlgo->TabIndex = 7;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 62);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 16);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Algorithm";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(32, 126);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(221, 26);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Open file and convert to B64";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(259, 127);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(232, 25);
			this->button5->TabIndex = 10;
			this->button5->Text = L"Save B64 encoded text into bin file";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(32, 158);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(553, 312);
			this->tabControl1->TabIndex = 11;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->richTextBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(545, 283);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Texto";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button10);
			this->tabPage2->Controls->Add(this->button9);
			this->tabPage2->Controls->Add(this->button8);
			this->tabPage2->Controls->Add(this->button7);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->numericUpDownSize);
			this->tabPage2->Controls->Add(this->comboBoxLetter);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->button6);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(545, 283);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Partição";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(223, 144);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(152, 23);
			this->button10->TabIndex = 9;
			this->button10->Text = L"Decrypt large files";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MainForm::button10_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(223, 115);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(152, 23);
			this->button9->TabIndex = 8;
			this->button9->Text = L"Encrypt large files";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MainForm::button9_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(53, 174);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(145, 23);
			this->button8->TabIndex = 7;
			this->button8->Text = L"Umount disk";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(53, 144);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(145, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Mount disk";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(177, 39);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 16);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Size In Mb";
			// 
			// numericUpDownSize
			// 
			this->numericUpDownSize->Location = System::Drawing::Point(179, 60);
			this->numericUpDownSize->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000000, 0, 0, 0 });
			this->numericUpDownSize->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->numericUpDownSize->Name = L"numericUpDownSize";
			this->numericUpDownSize->Size = System::Drawing::Size(120, 22);
			this->numericUpDownSize->TabIndex = 4;
			this->numericUpDownSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			// 
			// comboBoxLetter
			// 
			this->comboBoxLetter->FormattingEnabled = true;
			this->comboBoxLetter->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"A", L"B", L"C", L"D", L"E", L"F", L"G",
					L"H", L"I", L"J"
			});
			this->comboBoxLetter->Location = System::Drawing::Point(53, 58);
			this->comboBoxLetter->Name = L"comboBoxLetter";
			this->comboBoxLetter->Size = System::Drawing::Size(68, 24);
			this->comboBoxLetter->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(50, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 16);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Letter";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(53, 115);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(145, 23);
			this->button6->TabIndex = 0;
			this->button6->Text = L"Create disk";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->button16);
			this->tabPage3->Controls->Add(this->button15);
			this->tabPage3->Controls->Add(this->button14);
			this->tabPage3->Controls->Add(this->dataGridView1);
			this->tabPage3->Controls->Add(this->button13);
			this->tabPage3->Controls->Add(this->button12);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(545, 283);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Database";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(356, 19);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(149, 23);
			this->button16->TabIndex = 5;
			this->button16->Text = L"Open decrypted DB";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MainForm::button16_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(6, 18);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(77, 24);
			this->button15->TabIndex = 4;
			this->button15->Text = L"Create";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &MainForm::button15_Click);
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(176, 18);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(84, 24);
			this->button14->TabIndex = 3;
			this->button14->Text = L"Save";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MainForm::button14_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(3, 57);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(534, 220);
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MainForm::dataGridView1_RowsAdded);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(266, 18);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(84, 24);
			this->button13->TabIndex = 1;
			this->button13->Text = L"Close";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MainForm::button13_Click);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(89, 18);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(84, 24);
			this->button12->TabIndex = 0;
			this->button12->Text = L"Open";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MainForm::button12_Click);
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->button19);
			this->tabPage4->Controls->Add(this->button18);
			this->tabPage4->Controls->Add(this->label5);
			this->tabPage4->Controls->Add(this->textBoxPassDec);
			this->tabPage4->Controls->Add(this->button17);
			this->tabPage4->Controls->Add(this->dataGridView2);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(545, 283);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Database Memory";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(146, 11);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(75, 23);
			this->button19->TabIndex = 5;
			this->button19->Text = L"Decrypt pass";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &MainForm::button19_Click);
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(87, 11);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(53, 23);
			this->button18->TabIndex = 4;
			this->button18->Text = L"Save";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &MainForm::button18_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(47, 255);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 16);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Password";
			// 
			// textBoxPassDec
			// 
			this->textBoxPassDec->Location = System::Drawing::Point(120, 252);
			this->textBoxPassDec->Name = L"textBoxPassDec";
			this->textBoxPassDec->Size = System::Drawing::Size(172, 22);
			this->textBoxPassDec->TabIndex = 2;
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(6, 11);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(75, 23);
			this->button17->TabIndex = 1;
			this->button17->Text = L"Create";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &MainForm::button17_Click);
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Location = System::Drawing::Point(6, 40);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->RowTemplate->Height = 24;
			this->dataGridView2->Size = System::Drawing::Size(516, 206);
			this->dataGridView2->TabIndex = 0;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(498, 81);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 12;
			this->button11->Text = L"SHA256";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MainForm::button11_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(636, 498);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBoxAlgo);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBoxPass);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSize))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		// Configurações opcionais do OpenFileDialog
		openFileDialog1->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				// Tentativa de abrir e ler o arquivo
				Stream^ fileStream = openFileDialog1->OpenFile();
				if (fileStream != nullptr) {
					StreamReader^ reader = gcnew StreamReader(fileStream);
					this->richTextBox1->Text = reader->ReadToEnd();
					reader->Close();
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Erro ao abrir o arquivo: " + ex->Message);
			}
		}


	}
	private: System::Void statusStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
private: System::Void toolStripStatusLabel1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	/*if (this->cipher->encode("www", "D:/ex.txt.cod")) {
		MessageBox::Show("Criptografou!", "Alerta", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else {
		MessageBox::Show("Falhou!", "Alerta", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}*/

	if (textBoxPass->TextLength != 16) {
		MessageBox::Show("Password must contain 16 characters", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		MessageBox::Show("Choose an algorithm to encrypt the message!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (richTextBox1->Text->Length <  5) {
		MessageBox::Show("The text must contain at least 5 characters!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	System::Windows::Forms::SaveFileDialog^ saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
	saveFileDialog->Filter = "Encrypted files (*.enc)|*.enc|All files (*.*)|*.*";
	saveFileDialog->FilterIndex = 1;
	saveFileDialog->RestoreDirectory = true;

	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if (comboBoxAlgo->SelectedItem == "AES256") {
			try {
				this->cipher->encode(richTextBox1->Text->ToString(), textBoxPass->Text, saveFileDialog->FileName);
				MessageBox::Show("File encrypted saved!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			catch (Exception^ e) {
				MessageBox::Show("Failed: " + e->Message);
			}
		}
	}

}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBoxPass->TextLength != 16) {
		MessageBox::Show("Password must contain 16 characters", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		MessageBox::Show("Choose an algorithm to encrypt the message!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	System::Windows::Forms::OpenFileDialog^ openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
	openFileDialog->Filter = "Encrypted files (*.enc)|*.enc|All files (*.*)|*.*";
	openFileDialog->FilterIndex = 1;
	openFileDialog->RestoreDirectory = true;

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if (comboBoxAlgo->SelectedItem == "AES256" && openFileDialog->FileName->Length > 0) {

			try {
				richTextBox1->Text = cipher->decode(openFileDialog->FileName, textBoxPass->Text);
				MessageBox::Show("Decrypted", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			catch (Exception^ e) {
				MessageBox::Show("Erro ao abrir o arquivo: " + e->Message, "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}

		}
	}

}

private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {

	System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
	fileDialog->Filter = "All files (*.*)|*.*";
	fileDialog->FilterIndex = 1;
	fileDialog->RestoreDirectory = true;


	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		try {
			FileStream^ fs = gcnew FileStream(fileDialog->FileName, FileMode::Open, FileAccess::Read);
			long fileSize = fs->Length;
			array<Byte>^ buffer = gcnew array<Byte>(fileSize);
			fs->Read(buffer, 0, fileSize);
			String^ base64String = System::Convert::ToBase64String(buffer);
			richTextBox1->Text = base64String;
			MessageBox::Show("File read!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed: " + e->Message);
		}
	}

}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {

	System::Windows::Forms::SaveFileDialog^ fileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
	fileDialog->Filter = "All files (*.*)|*.*";
	fileDialog->FilterIndex = 1;
	fileDialog->RestoreDirectory = true;

	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		try {
			// Converter Base64 para array de bytes
			array<Byte>^ binaryData = System::Convert::FromBase64String(richTextBox1->Text);

			// Caminho onde você quer salvar o arquivo binário
			String^ outputFileName = fileDialog->FileName;

			// Salvar os dados binários em um arquivo
			FileStream^ fs = gcnew FileStream(outputFileName, FileMode::Create, FileAccess::Write);
			fs->Write(binaryData, 0, binaryData->Length);
			fs->Close(); // Fechar o FileStream
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed: " + e->Message);
		}
	}

}

private: System::String^ removeExtension(System::String^ filePath) {
	System::String^ fileToSave = "";
	array<System::String^>^ parts = filePath->Split('.');
	for (int i = 0; i < (parts->Length - 1); i++) {
		if (i > 0) {
			fileToSave = fileToSave + ".";
		}
		fileToSave = fileToSave + parts[i];
	}
	return fileToSave;
}

private: System::Void invalidParameters() {

	if (textBoxPass->TextLength != 16) {
		throw gcnew System::Exception("Password must contain 16 characters");
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		throw gcnew System::Exception("Choose an algorithm to encrypt the message!");
	}

}

//Create disk
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {

	try {

		System::Windows::Forms::SaveFileDialog^ fileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
		fileDialog->Filter = "VHD files (*.vhd)|*.vhd";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			invalidParameters();

			if (this->comboBoxLetter->Text->Length < 1) {
				throw gcnew Exception("Choose an unit letter");
			}

			System::String^ filePath = fileDialog->FileName;
			System::String^ letter = this->comboBoxLetter->Text;

			VirtualDisk^ vd = gcnew VirtualDisk(letter, filePath, System::Decimal::ToInt32(numericUpDownSize->Value), false);
			vd->run();
			cipher->encodeLargeFiles(filePath, textBoxPass->Text, filePath + ".enc");
			cipher->eraseFile(filePath);

		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}

}

// Mount disk
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	
	try {

		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "ENC files (*.enc)|*.enc";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			invalidParameters();

			if (this->comboBoxLetter->Text->Length < 1) {
				throw gcnew Exception("Choose an unit letter");
			}

			System::String^ filePath = fileDialog->FileName;
			System::String^ letter = this->comboBoxLetter->Text;

			System::String^ fileToSave = removeExtension(filePath); //remove enc extension
			cipher->decodeLargeFiles(filePath, textBoxPass->Text, fileToSave);
			cipher->eraseFile(filePath);

			VirtualDisk^ vd = gcnew VirtualDisk(letter, fileToSave, System::Decimal::ToInt32(numericUpDownSize->Value), false);
			vd->mount();

		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}

}

// Umount disk
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	
	try {

		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "VHD files (*.vhd)|*.vhd";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;

		invalidParameters();

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			if (this->comboBoxLetter->Text->Length < 1) {
				throw gcnew Exception("Choose an unit letter");
			}

			System::String^ filePath = fileDialog->FileName;
			System::String^ letter = this->comboBoxLetter->Text;

			VirtualDisk^ vd = gcnew VirtualDisk(letter, filePath, System::Decimal::ToInt32(numericUpDownSize->Value), false);
			vd->umount();

			cipher->encodeLargeFiles(filePath, textBoxPass->Text, filePath + ".enc");
			cipher->eraseFile(filePath);

		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}

}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	//Encrypt large files

	try {

		invalidParameters();

		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "All files (*.*)|*.*";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			System::String^ filePath = fileDialog->FileName;
			cipher->encodeLargeFiles(filePath, textBoxPass->Text, filePath + ".enc");
			cipher->eraseFile(filePath);

			MessageBox::Show("Filed encrypted!");
		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}

}
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
	//Decrypt large files

	try {

		invalidParameters();

		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "Encrypted files (*.enc)|*.enc";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;

		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			
			System::String^ filePath = fileDialog->FileName;
			System::String^ fileToSave = removeExtension(filePath);

			cipher->decodeLargeFiles(filePath, textBoxPass->Text, fileToSave);
			cipher->eraseFile(filePath);
			MessageBox::Show("Filed decrypted!");
		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}
}
private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {

	try {

		std::vector<unsigned char> sha = cipher->sha256(this->textBoxPass->Text);
		richTextBox1->Text = "";

		for (int i = 0; i < sha.size(); i++) {
			richTextBox1->Text += System::String::Format("{0:X2}", sha[i]);
		}

	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
	}

}

private:
	DatabaseHandler ^databaseHandler = nullptr;

#define CHECK_DATABASE_HANDLER() do { if (databaseHandler == nullptr) { \
	MessageBox::Show("Open a database first!"); \
	return; \
	} } while (0)


private: void DataGridView_RowsRemoved(Object^ sender, DataGridViewRowCancelEventArgs^ e) {

	if (databaseHandler == nullptr) {
		return;
	}

	DataGridViewRow^ row = e->Row;

	if (row == nullptr) {
		return;
	}

	if (row->Cells["ID"] == nullptr || row->Cells["ID"] == nullptr) {
		MessageBox::Show("There is no ID!");
		return;
	}

	int id = safe_cast<int>(row->Cells["ID"]->Value);

	if (id > 0) {
		try {
			databaseHandler->removeItem(id);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Failed to remove item " + ex->Message);
		}
	}

}

private: void initializeDataGrid() {

	dataGridView1->Columns->Clear();

	// Column for ID
	DataGridViewColumn^ idColumn = gcnew DataGridViewTextBoxColumn();
	idColumn->Name = "ID";
	idColumn->HeaderText = "ID";
	idColumn->DataPropertyName = "ID";  // If binding to a data source
	idColumn->Width = 50;
	dataGridView1->Columns->Add(idColumn);

	// Column for Name
	DataGridViewColumn^ urlColumn = gcnew DataGridViewTextBoxColumn();
	urlColumn->Name = "URL";
	urlColumn->HeaderText = "URL";
	urlColumn->DataPropertyName = "URL";  // If binding to a data source
	urlColumn->Width = 150;
	dataGridView1->Columns->Add(urlColumn);

	// Column for Login
	DataGridViewColumn^ loginColumn = gcnew DataGridViewTextBoxColumn();
	loginColumn->Name = "Login";
	loginColumn->HeaderText = "Login";
	loginColumn->DataPropertyName = "Login";  // If binding to a data source
	loginColumn->Width = 150;
	dataGridView1->Columns->Add(loginColumn);

	// Column for Name
	DataGridViewColumn^ passColumn = gcnew DataGridViewTextBoxColumn();
	passColumn->Name = "Password";
	passColumn->HeaderText = "Password";
	passColumn->DataPropertyName = "Password";  // If binding to a data source
	passColumn->Width = 150;
	dataGridView1->Columns->Add(passColumn);

	dataGridView1->Columns["ID"]->ReadOnly = true;

}

private: void reloadDatabase() {

	dataGridView1->UserDeletingRow -= gcnew DataGridViewRowCancelEventHandler(this, &MainForm::DataGridView_RowsRemoved);

	//dataGridView1->Rows->Clear();
	
	System::Collections::Generic::List<Credential^>^ credentials = databaseHandler->getCredentials();

	DataTable^ table = gcnew DataTable();

	table->Columns->Add("ID", System::Type::GetType("System.Int32"));
	table->Columns->Add("url", System::Type::GetType("System.String"));
	table->Columns->Add("login", System::Type::GetType("System.String"));
	table->Columns->Add("password", System::Type::GetType("System.String"));

	for (int i = 0; i < credentials->Count; i++) {
		DataRow^ row = table->NewRow();
		row["ID"] = credentials[i]->Id;
		row["url"] = credentials[i]->Url;
		row["login"] = credentials[i]->Login;
		row["password"] = credentials[i]->Password;

		table->Rows->Add(row);
	}

	dataGridView1->DataSource = table;

	dataGridView1->UserDeletingRow += gcnew DataGridViewRowCancelEventHandler(this, &MainForm::DataGridView_RowsRemoved);
}

// Open Databse
private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBoxPass->TextLength != 16) {
		MessageBox::Show("Password must contain 16 characters");
		return;
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		MessageBox::Show("Choose an algorithm to encrypt the message!");
		return;
	}

	if (databaseHandler != nullptr) {
		MessageBox::Show("Close the current database before opening another one!");
		return;
	}

	try {
		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "Encrypted database files (*.enc)|*.enc";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;
		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			System::String ^fileNameDb = removeExtension(fileDialog->FileName);
			cipher->decodeLargeFiles(fileDialog->FileName, textBoxPass->Text, fileNameDb);
			cipher->eraseFile(fileDialog->FileName);
			databaseHandler = gcnew DatabaseHandler(fileNameDb);
		}

	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
		return;
	}

	initializeDataGrid();
	reloadDatabase();

	
}
// Close
private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBoxPass->TextLength != 16) {
		MessageBox::Show("Password must contain 16 characters", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		MessageBox::Show("Choose an algorithm to encrypt the message!", "Alert", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	dataGridView1->UserDeletingRow -= gcnew DataGridViewRowCancelEventHandler(this, &MainForm::DataGridView_RowsRemoved);


	System::String ^fileName = databaseHandler->getFileName();
	delete databaseHandler;
	databaseHandler = nullptr;

	cipher->encodeLargeFiles(fileName, textBoxPass->Text, fileName + ".enc");
	cipher->eraseFile(fileName);

	dataGridView1->Columns->Clear();

}
private: System::Void dataGridView1_RowsAdded(System::Object^ sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^ e) {

}

// Save
private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {

	CHECK_DATABASE_HANDLER();

	for (int i = 0; i < dataGridView1->Rows->Count; i++) {

		if (dataGridView1->Rows[i]->Cells["ID"] != nullptr && 
			(dataGridView1->Rows[i]->Cells["ID"]->Value != nullptr && dataGridView1->Rows[i]->Cells["ID"]->Value->ToString()->Length < 1 )) {
			databaseHandler->addItem(
				dataGridView1->Rows[i]->Cells["URL"]->Value->ToString(), 
				dataGridView1->Rows[i]->Cells["Login"]->Value->ToString(),
				dataGridView1->Rows[i]->Cells["Password"]->Value->ToString());
		}
	}

	initializeDataGrid();
	reloadDatabase();

	databaseHandler->commit();
}

// Create
private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {

	if (databaseHandler != nullptr) {
		MessageBox::Show("Close the current database before creating another one!");
		return;
	}

	try {
		System::Windows::Forms::SaveFileDialog^ fileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
		fileDialog->Filter = "Database files (*.db)|*.db";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;
		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			databaseHandler = gcnew DatabaseHandler(fileDialog->FileName);
		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
		return;
	}

	initializeDataGrid();
	reloadDatabase();

}
private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {

	if (databaseHandler != nullptr) {
		MessageBox::Show("Close the current database before opening another one!");
		return;
	}

	try {
		System::Windows::Forms::OpenFileDialog^ fileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
		fileDialog->Filter = "Database files (*.db)|*.db";
		fileDialog->FilterIndex = 1;
		fileDialog->RestoreDirectory = true;
		if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			databaseHandler = gcnew DatabaseHandler(fileDialog->FileName);
		}

	}
	catch (Exception^ e) {
		MessageBox::Show("Failed: " + e->Message);
		return;
	}

	initializeDataGrid();
	reloadDatabase();

}

private:
#define CHECK_DATABASE_RAM_HANDLER() do { if (databaseRAMHandler == nullptr) { \
	MessageBox::Show("Open a database first!"); \
	return; \
	} } while (0)


	DatabaseRAMHandler ^databaseRAMHandler = nullptr;

	void initializeDBRAM() {
		dataGridView2->Columns->Clear();

		// Column for ID
		DataGridViewColumn^ idColumn = gcnew DataGridViewTextBoxColumn();
		idColumn->Name = "ID";
		idColumn->HeaderText = "ID";
		idColumn->DataPropertyName = "ID";  // If binding to a data source
		idColumn->Width = 50;
		dataGridView2->Columns->Add(idColumn);

		// Column for Name
		DataGridViewColumn^ urlColumn = gcnew DataGridViewTextBoxColumn();
		urlColumn->Name = "URL";
		urlColumn->HeaderText = "URL";
		urlColumn->DataPropertyName = "URL";  // If binding to a data source
		urlColumn->Width = 150;
		dataGridView2->Columns->Add(urlColumn);

		// Column for Login
		DataGridViewColumn^ loginColumn = gcnew DataGridViewTextBoxColumn();
		loginColumn->Name = "Login";
		loginColumn->HeaderText = "Login";
		loginColumn->DataPropertyName = "Login";  // If binding to a data source
		loginColumn->Width = 150;
		dataGridView2->Columns->Add(loginColumn);

		DataGridViewColumn^ passColumn = gcnew DataGridViewTextBoxColumn();
		passColumn->Name = "Password";
		passColumn->HeaderText = "Password";
		passColumn->DataPropertyName = "Password";  // If binding to a data source
		passColumn->Width = 150;
		dataGridView2->Columns->Add(passColumn);

	}

	void reloadDatabaseRAM() {
		//dataGridView1->UserDeletingRow -= gcnew DataGridViewRowCancelEventHandler(this, &MainForm::DataGridView_RowsRemoved);

		System::Collections::Generic::List<Credential^>^ credentials = databaseRAMHandler->getCredentials();

		DataTable^ table = gcnew DataTable();

		table->Columns->Add("ID", System::Type::GetType("System.Int32"));
		table->Columns->Add("url", System::Type::GetType("System.String"));
		table->Columns->Add("login", System::Type::GetType("System.String"));
		table->Columns->Add("password", System::Type::GetType("System.String"));

		for (int i = 0; i < credentials->Count; i++) {
			DataRow^ row = table->NewRow();
			row["ID"] = credentials[i]->Id;
			row["url"] = credentials[i]->Url;
			row["login"] = credentials[i]->Login;
			row["password"] = credentials[i]->Password;

			table->Rows->Add(row);
		}

		dataGridView2->DataSource = table;

		//dataGridView2->UserDeletingRow += gcnew DataGridViewRowCancelEventHandler(this, &MainForm::DataGridView_RowsRemoved);
	}

	// create DB RAM
private: System::Void button17_Click(System::Object^ sender, System::EventArgs^ e) {
	if (databaseRAMHandler != nullptr) {
		delete databaseRAMHandler;
	}
	databaseRAMHandler = gcnew DatabaseRAMHandler(DB_RAM, cipher);
	initializeDBRAM();
	reloadDatabaseRAM();
}

	   // save DB RAM
private: System::Void button18_Click(System::Object^ sender, System::EventArgs^ e) {
	CHECK_DATABASE_RAM_HANDLER();

	if (textBoxPass->TextLength != 16) {
		MessageBox::Show("Password must contain 16 characters");
		return;
	}

	if (comboBoxAlgo->SelectedIndex == -1) {
		MessageBox::Show("Choose an algorithm to encrypt the message!");
		return;
	}

	if (databaseRAMHandler->getType() == DB_RAM) {

		for (int i = 0; i < dataGridView2->Rows->Count; i++) {

			if (dataGridView2->Rows[i]->Cells["ID"] != nullptr &&
				(dataGridView2->Rows[i]->Cells["ID"]->Value != nullptr &&
					dataGridView2->Rows[i]->Cells["ID"]->Value->ToString()->Length < 1)) {

				System::String^ pass = Convert::ToBase64String(cipher->encodeText(dataGridView2->Rows[i]->Cells["Password"]->Value->ToString(),
					textBoxPass->Text, 1024));

				databaseRAMHandler->addItem(
					dataGridView2->Rows[i]->Cells["URL"]->Value->ToString(),
					dataGridView2->Rows[i]->Cells["Login"]->Value->ToString(),
					pass);
			}
		}

		initializeDBRAM();
		reloadDatabaseRAM();

		//databaseRAMHandler->commit();

	}
}
	   // decrypt RAM
private: System::Void button19_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dataGridView2->SelectedRows->Count != 1) {
		MessageBox::Show("Select only one row!");
	}
	else {
		// Pega a primeira linha selecionada
		DataGridViewRow^ selectedRow = dataGridView2->SelectedRows[0];
		// TODO
	}
}
};
}
