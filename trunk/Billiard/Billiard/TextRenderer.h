#include <Ogre.h>
#include <OgreSingleton.h>
#include "OgreStringConverter.h"

class TextRenderer : public Ogre::Singleton<TextRenderer>
{
private:

	Ogre::OverlayManager*    _overlayMgr;
	Ogre::Overlay*           _overlay;
	Ogre::OverlayContainer*  _panel;

public:

	TextRenderer();
	~TextRenderer();

	void addTextBox(
		const std::string& ID,
		const std::string& text,
		Ogre::Real x, Ogre::Real y,
		Ogre::Real width, Ogre::Real height,
		const Ogre::ColourValue& color = Ogre::ColourValue(1.0, 1.0, 1.0, 1.0));

	void removeTextBox(const std::string& ID);

	void setText(const std::string& ID, const std::string& Text);
	void TextRenderer::setPosition(const std::string& ID,Ogre::Real x, Ogre::Real y);
	void TextRenderer::setCharHeight(const std::string& ID, Ogre::Real c_height);
};
