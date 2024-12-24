#pragma once
#include <vcclr.h>


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
			this->statusStrip1->SuspendLayout();
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
			this->statusStrip1->Location = System::Drawing::Point(0, 456);
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
			this->richTextBox1->Location = System::Drawing::Point(32, 179);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(553, 274);
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
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(623, 482);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBoxAlgo);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBoxPass);
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
};
}
