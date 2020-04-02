#pragma once
#include <msclr\marshal_cppstd.h>
#include "MainEngine.h"


namespace CoreSegregationDetector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:


		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			
			MainEngine^ mainEngine = gcnew MainEngine();
			//ThreadX^ o1 = gcnew ThreadX
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  openFileButton;
	protected:

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		//System::String^ filePath;
		MainEngine^ mainEngine;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  loadingLabel;

	private: System::ComponentModel::IContainer^  components;
			 /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->openFileButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->loadingLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileButton
			// 
			this->openFileButton->Location = System::Drawing::Point(12, 12);
			this->openFileButton->Name = L"openFileButton";
			this->openFileButton->Size = System::Drawing::Size(75, 23);
			this->openFileButton->TabIndex = 0;
			this->openFileButton->Text = L"Open Image";
			this->openFileButton->UseVisualStyleBackColor = true;
			this->openFileButton->Click += gcnew System::EventHandler(this, &MyForm::openFileButton_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Silver;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBox1->Location = System::Drawing::Point(12, 41);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(853, 640);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Silver;
			this->pictureBox2->Cursor = System::Windows::Forms::Cursors::Default;
			this->pictureBox2->Location = System::Drawing::Point(871, 41);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(853, 640);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// loadingLabel
			// 
			this->loadingLabel->AutoSize = true;
			this->loadingLabel->Location = System::Drawing::Point(93, 17);
			this->loadingLabel->Name = L"loadingLabel";
			this->loadingLabel->Size = System::Drawing::Size(80, 13);
			this->loadingLabel->TabIndex = 3;
			this->loadingLabel->Text = L"Loading Data...";
			this->loadingLabel->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1735, 813);
			this->Controls->Add(this->loadingLabel);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->openFileButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void openFileButton_Click(System::Object^  sender, System::EventArgs^  e) {
			IO::Stream^ myStream;
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			System::String^ filePath;

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if ((myStream = openFileDialog1->OpenFile()) != nullptr)
				{
					// Insert code to read the stream here.
					filePath = gcnew System::String(openFileDialog1->FileName);
					mainEngine = gcnew MainEngine(filePath);
					myStream->Close();

					//mainEngine->SetPath(filePath);
					System::Threading::Thread^ t1 = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(mainEngine, &MainEngine::RunCalculation));
					//mainEngine->RunCalculation(msclr::interop::marshal_as<std::string>(openFileDialog1->FileName));
					//System::Drawing::Bitmap dupa = msclr::interop::marshal_as<System::Drawing::Bitmap>(mainEngine->originalImage);
					//Bitmap^ resized = gcnew System::Drawing::Bitmap(mainEngine->originalImage, new System::Drawing::Size(853, 640)));
					//pictureBox1->Image = mainEngine->originalImage;
					t1->Start();
					timer1->Enabled = true;
					loadingLabel->Visible = true;
					//pictureBox1->Image = mainEngine->originalImage;
					//pictureBox2->Image = mainEngine->editedImage;
				}
			}
			//this->filePath = filePath;


		}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (mainEngine->originalImageReady) {
			pictureBox1->Image = mainEngine->originalImage;
		}
		if (mainEngine->editedImageReady) {
			pictureBox2->Image = mainEngine->editedImage;
		}
		if (mainEngine->calculationsReady) {
			timer1->Enabled = false;
			loadingLabel->Visible = false;
			//wypisz wyniki
		}
	}
};
}
