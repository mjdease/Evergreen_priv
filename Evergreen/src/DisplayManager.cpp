#include "DisplayManager.h"

DisplayManager::DisplayManager(void)
{

}

void DisplayManager::addtoLayer(EverTexture* tx, int layerNumber) {
	layers[layerNumber]->addtoDraw(tx);
}

int DisplayManager::newLayer() {
	Layer* temp = new Layer();
	layers.push_back(temp);
	return (layers.size() - 1);
}

void DisplayManager::drawLayer(int layerIndex) {
	// draw a layer
	layers[layerIndex]->draw();
}

void DisplayManager::draw() {
	for(int i = 0; i < layers.size(); i++) {
		drawLayer(i);
	}
}

DisplayManager::~DisplayManager(void)
{

}

//DisplayManager::DisplayManager(void)
//{
//	ofSetColor(255);
//	// load background images
//	foreground.loadImage("environment/foreground.bmp");
//	midground.loadImage("environment/midground.bmp");
//	background.loadImage("environment/background.png");
//
//	// load background image alpha mask
//	midground_a.loadImage("environment/midground_a.bmp");
//	mix[0] = getMask(midground,midground_a);
//
//	foreground_a.loadImage("environment/foreground_a.bmp");
//	mix[1] = getMask(foreground,foreground_a);
//}

//void DisplayManager::drawLayers() {
//	
//	background.draw(0,0);
//
//	ofEnableAlphaBlending();
//		mix[0].draw(0,0);
//		mix[1].draw(0,0);
//	ofDisableAlphaBlending();
//
//}

//ofTexture DisplayManager::getMask(ofImage img, ofImage img_a) {
//	
//	ofTexture mix;
//
//	img_a.setImageType(OF_IMAGE_GRAYSCALE);
//
//	int w = img.width;
//	int h = img.height;
//
//	unsigned char * px = new unsigned char [w*h*4];
//	unsigned char * pxColor = img.getPixels();
//	unsigned char * pxA = img_a.getPixels();
//
//	// get all pixels and put in px
//	for(int i = 0; i < w; i++) {
//		for(int j = 0; j < h; j++) {
//
//			int position = (j * w + i);
//			
//			px[position * 4]   = pxColor[position * 3];
//			px[position * 4+1] = pxColor[position * 3+1];
//			px[position * 4+2] = pxColor[position * 3+2];
//			px[position * 4+3] = pxA[position];
//
//		}
//	}
//
//	mix.allocate(w,h,GL_RGBA);
//	mix.loadData(px,w,h,GL_RGBA);
//
//	delete [] px;
//
//	return mix;
//}