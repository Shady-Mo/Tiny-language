#pragma once
#include "lexerlogic.h"
#include "ParserLogic.h"
#include <msclr/marshal_cppstd.h>
namespace compilergui
{
	using namespace msclr::interop;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

public
	ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			parserTokens = gcnew List<String ^>();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::TextBox ^ textBox1;
		System::Windows::Forms::Label ^ label1;
		System::Windows::Forms::Button ^ button1;
		System::Windows::Forms::DataGridView ^ dataGridView1;
		System::Windows::Forms::DataGridViewTextBoxColumn ^ Column1;
		System::Windows::Forms::DataGridViewTextBoxColumn ^ Column2;
		System::Windows::Forms::RichTextBox ^ richTextBoxParserOutput;
		System::Windows::Forms::Label ^ labelParserTitle;
		System::Windows::Forms::Label ^ labelTokensTitle;
		System::Windows::Forms::Button ^ buttonParse;
		System::ComponentModel::Container ^ components;
		List<String ^> ^ parserTokens;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// [Existing InitializeComponent code remains unchanged]
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->richTextBoxParserOutput = (gcnew System::Windows::Forms::RichTextBox());
			this->labelParserTitle = (gcnew System::Windows::Forms::Label());
			this->labelTokensTitle = (gcnew System::Windows::Forms::Label());
			this->buttonParse = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();

			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(266, 41);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(460, 100);
			this->textBox1->TabIndex = 0;

			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(97, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Please Enter Text :";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);

			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(266, 155);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 33);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Lexical Analysis";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);

			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array<System::Windows::Forms::DataGridViewColumn ^>(2){this->Column1, this->Column2});
			this->dataGridView1->Location = System::Drawing::Point(41, 228);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(369, 287);
			this->dataGridView1->TabIndex = 3;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellContentClick);

			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column1->HeaderText = L"Lexeme";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;

			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column2->HeaderText = L"Token";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;

			this->richTextBoxParserOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBoxParserOutput->Location = System::Drawing::Point(430, 228);
			this->richTextBoxParserOutput->Name = L"richTextBoxParserOutput";
			this->richTextBoxParserOutput->Size = System::Drawing::Size(369, 287);
			this->richTextBoxParserOutput->TabIndex = 4;
			this->richTextBoxParserOutput->Text = L"";

			this->labelParserTitle->AutoSize = true;
			this->labelParserTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelParserTitle->Location = System::Drawing::Point(430, 208);
			this->labelParserTitle->Name = L"labelParserTitle";
			this->labelParserTitle->Size = System::Drawing::Size(139, 15);
			this->labelParserTitle->TabIndex = 5;
			this->labelParserTitle->Text = L"Parser Analysis Results";

			this->labelTokensTitle->AutoSize = true;
			this->labelTokensTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelTokensTitle->Location = System::Drawing::Point(41, 208);
			this->labelTokensTitle->Name = L"labelTokensTitle";
			this->labelTokensTitle->Size = System::Drawing::Size(151, 15);
			this->labelTokensTitle->TabIndex = 6;
			this->labelTokensTitle->Text = L"Lexical Analysis Results";

			this->buttonParse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->buttonParse->Location = System::Drawing::Point(415, 155);
			this->buttonParse->Name = L"buttonParse";
			this->buttonParse->Size = System::Drawing::Size(117, 33);
			this->buttonParse->TabIndex = 7;
			this->buttonParse->Text = L"Parse";
			this->buttonParse->UseVisualStyleBackColor = true;
			this->buttonParse->Click += gcnew System::EventHandler(this, &MainForm::buttonParse_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ClientSize = System::Drawing::Size(822, 540);
			this->Controls->Add(this->buttonParse);
			this->Controls->Add(this->labelTokensTitle);
			this->Controls->Add(this->labelParserTitle);
			this->Controls->Add(this->richTextBoxParserOutput);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Tiny Language Compiler";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private:
		System::Void label1_Click(System::Object ^ sender, System::EventArgs ^ e) {}
		System::Void button1_Click(System::Object ^ sender, System::EventArgs ^ e)
		{
			dataGridView1->Rows->Clear();
			richTextBoxParserOutput->Clear();
			std::string input = msclr::interop::marshal_as<std::string>(textBox1->Text);
			std::vector<Token> tokens = tokenize(input);
			for (const auto &token : tokens)
			{
				std::string typeStr = tokenTypeToString(token.type, token.lexeme);
				String ^ lexeme = gcnew String(token.lexeme.c_str());
				String ^ type = gcnew String(typeStr.c_str());
				array<String ^> ^ row = gcnew array<String ^>{lexeme, type};
				dataGridView1->Rows->Add(row);
			}
		}
		void ExtractParserTokens(const std::vector<Token> &lexerTokens)
		{
			parserTokens = gcnew System::Collections::Generic::List<System::String ^>();
			for (const auto &token : lexerTokens)
			{
				if (token.type == COMMENT)
					continue;
				parserTokens->Add(gcnew String(token.lexeme.c_str()));
			}
		}
		System::Void buttonParse_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Convert input from TextBox to std::string
			std::string input = msclr::interop::marshal_as<std::string>(textBox1->Text);

			// Tokenize the input to get a vector of Token objects
			std::vector<Token> tokens = tokenize(input);

			// Ensure tokens are of type std::vector<Token>
			if (tokens.empty())
			{
				richTextBoxParserOutput->SelectionColor = System::Drawing::Color::Red;
				richTextBoxParserOutput->AppendText("No tokens found. Please check your input.\n");
				return;
			}

			// Pass the vector of Token objects directly to the Parser constructor
			Parser parser(tokens);

			// Parse the tokens
			bool success = parser.parse();

			// Retrieve parsing errors
			std::vector<ParseError> errors = parser.getErrors();

			// Clear the RichTextBox for parser output
			richTextBoxParserOutput->Clear();

			// Display parsing results
			if (success)
			{
				richTextBoxParserOutput->SelectionColor = System::Drawing::Color::Green;
				richTextBoxParserOutput->AppendText("Parsing successful!\n");
			}
			else
			{
				richTextBoxParserOutput->SelectionColor = System::Drawing::Color::Red;
				richTextBoxParserOutput->AppendText("Parsing failed with errors:\n\n");

				// Display each error
				for (const auto& error : errors)
				{
					String^ errorMsg = String::Format(
						"Error: {0}\nLine: {1} | Token: {2}\n\n",
						gcnew String(error.message.c_str()),
						error.line.ToString(),
						gcnew String(error.tokenValue.c_str()));
					richTextBoxParserOutput->AppendText(errorMsg);
				}
			}
		}
		System::Void dataGridView1_CellContentClick(System::Object ^ sender, System::Windows::Forms::DataGridViewCellEventArgs ^ e) {}
		System::Void MainForm_Load(System::Object ^ sender, System::EventArgs ^ e) {}
	};
}