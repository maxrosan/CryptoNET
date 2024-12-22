#pragma once

#include "Cipher.h"

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
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button3;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(32, 28);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(259, 22);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(311, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(76, 27);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Abrir Txt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Senha";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 372);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(623, 26);
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
			this->richTextBox1->Location = System::Drawing::Point(32, 75);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(553, 284);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(490, 28);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(79, 27);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Salvar";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(393, 28);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(91, 27);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Abrir Cod";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(623, 398);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
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
	if (this->cipher->encode("www", "D:/ex.txt.cod")) {
		MessageBox::Show("Criptografou!", "Alerta", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else {
		MessageBox::Show("Falhou!", "Alerta", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}
};
}
