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
			toolTip1->SetToolTip(segregationSizeLable, "Percentage value of segregation size compared to sample size.");
			toolTip2->SetToolTip(segregationIntensityLabel, "Measure of segregatation color in comparison with entire image colors.");
			toolTip3->SetToolTip(segregationValueLabel, "Wighted mean of particular segregation classes assesment.");
			toolTip4->SetToolTip(minimalColorLabel, "Color value of darkest pixel on image. Used to calculate segregations intensity.");
			toolTip5->SetToolTip(maximalColorLabel, "Color value of brightest pixel on image. Used to calculate segregations intensity.");
			toolTip6->SetToolTip(outerMeanColorLabel, "Mean color value of sample oter ring (solid color). This are is usually considered mean value for entire sample (excluding segregation). Used to calculate segregations intensity.");
			toolTip7->SetToolTip(segregationColorValueLabel, "Color treshold value used to seperate segregation from rest of sample in first step or recognition.");
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
	private: System::Windows::Forms::Label^  calculationsLabel;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  segregationIntensityLabel;
	private: System::Windows::Forms::Label^  segregationSizeLable;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  minimalColorLabel;
	private: System::Windows::Forms::Label^  outerMeanColorLabel;
	private: System::Windows::Forms::Label^  maximalColorLabel;
	private: System::Windows::Forms::Label^  segregationColorValueLabel;
	private: System::Windows::Forms::Label^  segregationValueLabel;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::ToolTip^  toolTip2;
	private: System::Windows::Forms::ToolTip^  toolTip3;
	private: System::Windows::Forms::ToolTip^  toolTip4;
	private: System::Windows::Forms::ToolTip^  toolTip5;
	private: System::Windows::Forms::ToolTip^  toolTip6;
	private: System::Windows::Forms::ToolTip^  toolTip7;




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
			this->calculationsLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->segregationValueLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->segregationIntensityLabel = (gcnew System::Windows::Forms::Label());
			this->segregationSizeLable = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->segregationColorValueLabel = (gcnew System::Windows::Forms::Label());
			this->outerMeanColorLabel = (gcnew System::Windows::Forms::Label());
			this->maximalColorLabel = (gcnew System::Windows::Forms::Label());
			this->minimalColorLabel = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip2 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip3 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip4 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip5 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip6 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip7 = (gcnew System::Windows::Forms::ToolTip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
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
			// calculationsLabel
			// 
			this->calculationsLabel->AutoSize = true;
			this->calculationsLabel->Location = System::Drawing::Point(93, 17);
			this->calculationsLabel->Name = L"calculationsLabel";
			this->calculationsLabel->Size = System::Drawing::Size(126, 13);
			this->calculationsLabel->TabIndex = 4;
			this->calculationsLabel->Text = L"Performing Calculations...";
			this->calculationsLabel->Visible = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->segregationValueLabel);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->segregationIntensityLabel);
			this->groupBox1->Controls->Add(this->segregationSizeLable);
			this->groupBox1->Location = System::Drawing::Point(219, 688);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(339, 100);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Measured segregation";
			// 
			// segregationValueLabel
			// 
			this->segregationValueLabel->AutoSize = true;
			this->segregationValueLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->segregationValueLabel->Location = System::Drawing::Point(71, 46);
			this->segregationValueLabel->Name = L"segregationValueLabel";
			this->segregationValueLabel->Size = System::Drawing::Size(29, 31);
			this->segregationValueLabel->TabIndex = 3;
			this->segregationValueLabel->Text = L"0";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Segregation:";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// segregationIntensityLabel
			// 
			this->segregationIntensityLabel->AutoSize = true;
			this->segregationIntensityLabel->Location = System::Drawing::Point(7, 33);
			this->segregationIntensityLabel->Name = L"segregationIntensityLabel";
			this->segregationIntensityLabel->Size = System::Drawing::Size(112, 13);
			this->segregationIntensityLabel->TabIndex = 1;
			this->segregationIntensityLabel->Text = L"Segregation Intensity: ";
			// 
			// segregationSizeLable
			// 
			this->segregationSizeLable->AutoSize = true;
			this->segregationSizeLable->Location = System::Drawing::Point(7, 20);
			this->segregationSizeLable->Name = L"segregationSizeLable";
			this->segregationSizeLable->Size = System::Drawing::Size(93, 13);
			this->segregationSizeLable->TabIndex = 0;
			this->segregationSizeLable->Text = L"Segregation Size: ";
			this->segregationSizeLable->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->segregationColorValueLabel);
			this->groupBox2->Controls->Add(this->outerMeanColorLabel);
			this->groupBox2->Controls->Add(this->maximalColorLabel);
			this->groupBox2->Controls->Add(this->minimalColorLabel);
			this->groupBox2->Location = System::Drawing::Point(13, 688);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 100);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Image parameters";
			// 
			// segregationColorValueLabel
			// 
			this->segregationColorValueLabel->AutoSize = true;
			this->segregationColorValueLabel->Location = System::Drawing::Point(6, 55);
			this->segregationColorValueLabel->Name = L"segregationColorValueLabel";
			this->segregationColorValueLabel->Size = System::Drawing::Size(136, 13);
			this->segregationColorValueLabel->TabIndex = 3;
			this->segregationColorValueLabel->Text = L"Segregation treshold color: ";
			// 
			// outerMeanColorLabel
			// 
			this->outerMeanColorLabel->AutoSize = true;
			this->outerMeanColorLabel->Location = System::Drawing::Point(6, 42);
			this->outerMeanColorLabel->Name = L"outerMeanColorLabel";
			this->outerMeanColorLabel->Size = System::Drawing::Size(114, 13);
			this->outerMeanColorLabel->TabIndex = 2;
			this->outerMeanColorLabel->Text = L"Outer ring mean color: ";
			// 
			// maximalColorLabel
			// 
			this->maximalColorLabel->AutoSize = true;
			this->maximalColorLabel->Location = System::Drawing::Point(6, 29);
			this->maximalColorLabel->Name = L"maximalColorLabel";
			this->maximalColorLabel->Size = System::Drawing::Size(77, 13);
			this->maximalColorLabel->TabIndex = 1;
			this->maximalColorLabel->Text = L"Maximal color: ";
			// 
			// minimalColorLabel
			// 
			this->minimalColorLabel->AutoSize = true;
			this->minimalColorLabel->Location = System::Drawing::Point(6, 16);
			this->minimalColorLabel->Name = L"minimalColorLabel";
			this->minimalColorLabel->Size = System::Drawing::Size(74, 13);
			this->minimalColorLabel->TabIndex = 0;
			this->minimalColorLabel->Text = L"Minimal color: ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1735, 813);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->calculationsLabel);
			this->Controls->Add(this->loadingLabel);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->openFileButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
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

					pictureBox1->Image = nullptr;
					pictureBox2->Image = nullptr;

					System::Threading::Thread^ t1 = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(mainEngine, &MainEngine::RunCalculation));
					t1->Start();
					timer1->Enabled = true;
					loadingLabel->Visible = true;
				}
			}
			//this->filePath = filePath;


		}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (mainEngine->originalImageReady) {
			pictureBox1->Image = mainEngine->originalImage;
			loadingLabel->Visible = false;
			calculationsLabel->Visible = true;
		}
		if (mainEngine->editedImageReady) {
			pictureBox2->Image = mainEngine->editedImage;
		}
		if (mainEngine->calculationsReady) {
			pictureBox1->Image = mainEngine->originalImage;
			pictureBox2->Image = mainEngine->editedImage;

			timer1->Enabled = false;
			loadingLabel->Visible = false;
			calculationsLabel->Visible = false;
			//wypisz wyniki
			segregationSizeLable->Text = "Segregation Size: " + mainEngine->getSegregationSize()*100 + "%";
			segregationIntensityLabel->Text = "Segregation Intensity: " + mainEngine->getSegregationIntensity();

			minimalColorLabel->Text = "Minimal color: " + mainEngine->getMinimalColorValue();
			maximalColorLabel->Text = "Maximal color: " + mainEngine->getMaximalColorValue();
			outerMeanColorLabel->Text = "Outer ring mean color:  " + mainEngine->getOuterRingMeanValue();
			segregationColorValueLabel->Text = "Segregation treshold color: " + mainEngine->getSegregationTresholdColorValue();
			segregationValueLabel->Text = mainEngine->getSegregationValue().ToString();

		}
	}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
