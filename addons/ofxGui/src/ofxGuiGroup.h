#pragma once
#include "ofxBaseGui.h"

#include "ofxSlider.h"
#include "ofxButton.h"
#include "ofParameterGroup.h"

class ofxGuiGroup : public ofxBaseGui {
	public:
		ofxGuiGroup();
		ofxGuiGroup(const ofParameterGroup & parameters, std::string _filename = "settings.xml", float x = 10, float y = 10);
		virtual ~ofxGuiGroup(){
		}
		virtual ofxGuiGroup * setup(std::string collectionName = "", std::string filename = "settings.xml", float x = 10, float y = 10);
		virtual ofxGuiGroup * setup(const ofParameterGroup & parameters, std::string filename = "settings.xml", float x = 10, float y = 10);

		void add(ofxBaseGui * element);
		void add(const ofParameterGroup & parameters);
		void add(ofParameter <float> & parameter);
		void add(ofParameter <int> & parameter);
		void add(ofParameter <bool> & parameter);
		void add(ofParameter <std::string> & parameter);
		void add(ofParameter <ofVec2f> & parameter);
		void add(ofParameter <ofVec3f> & parameter);
		void add(ofParameter <ofVec4f> & parameter);
		void add(ofParameter <ofColor> & parameter);
		void add(ofParameter <ofShortColor> & parameter);
		void add(ofParameter <ofFloatColor> & parameter);

		void minimize();
		void maximize();
		void minimizeAll();
		void maximizeAll();

		void setWidthElements(float w);

		void clear();

		virtual void sizeChangedCB();

		virtual bool mouseMoved(ofMouseEventArgs & args);
		virtual bool mousePressed(ofMouseEventArgs & args);
		virtual bool mouseDragged(ofMouseEventArgs & args);
		virtual bool mouseReleased(ofMouseEventArgs & args);
		virtual bool mouseScrolled(ofMouseEventArgs & args);


		std::vector <std::string> getControlNames();
		int getNumControls();

		ofxIntSlider & getIntSlider(std::string name);
		ofxFloatSlider & getFloatSlider(std::string name);
		ofxToggle & getToggle(std::string name);
		ofxButton & getButton(std::string name);
		ofxGuiGroup & getGroup(std::string name);

		ofxBaseGui * getControl(std::string name);
		ofxBaseGui * getControl(int num);

		virtual ofAbstractParameter & getParameter();

		virtual void setPosition(ofPoint p);
		virtual void setPosition(float x, float y);
	protected:
		virtual void render();
		virtual bool setValue(float mx, float my, bool bCheck);

		float spacing, spacingNextElement;
		float header;

		template <class ControlType>
		ControlType & getControlType(std::string name);

		virtual void generateDraw();

		std::vector <ofxBaseGui *> collection;
		ofParameterGroup parameters;

		std::string filename;
		bool minimized;
		bool bGuiActive;

		ofPath border, headerBg;
		ofVboMesh textMesh;
};

template <class ControlType>
ControlType & ofxGuiGroup::getControlType(std::string name){
	ControlType * control = dynamic_cast <ControlType *>(getControl(name));
	if(control){
		return *control;
	}else{
		ofLogWarning() << "getControlType " << name << " not found, creating new";
		control = new ControlType;
		control->setName(name);
		add(control);
		return *control;
	}
}
