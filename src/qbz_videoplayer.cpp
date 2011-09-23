#include "qbz_videoplayer.h"


bool _createMovieFromPath(char * path, Movie &movie);

bool _createMovieFromPath(char * path, Movie &movie){
	Boolean isdir = false;
	OSErr result = 0;
	FSSpec theFSSpec;

	short 		actualResId 	= DoTheRightThing;

		FSRef 		fsref;
		result = FSPathMakeRef((const UInt8*)path, &fsref, &isdir);
		if (result) {
			ofLog(OF_LOG_ERROR,"FSPathMakeRef failed %d", result);
			ofLog(OF_LOG_ERROR,"Error loading movie");
			return false;
		}
		result = FSGetCatalogInfo(&fsref, kFSCatInfoNone, NULL, NULL, &theFSSpec, NULL);
		if (result) {
			ofLog(OF_LOG_ERROR,"FSGetCatalogInfo failed %d", result);
			ofLog(OF_LOG_ERROR,"Error loading movie");
			return false;
		}

	short movieResFile;
	result = OpenMovieFile (&theFSSpec, &movieResFile, fsRdPerm);
	if (result == noErr) {

		short   movieResID = 0;
		result = NewMovieFromFile(&movie, movieResFile, &movieResID, (unsigned char *) 0, newMovieActive, (Boolean *) 0);
		if (result == noErr){
			CloseMovieFile (movieResFile);
		} else {
			ofLog(OF_LOG_ERROR,"NewMovieFromFile failed %d", result);
			return false;
		}
	} else {
		ofLog(OF_LOG_ERROR,"OpenMovieFile failed %d", result);
		return false;
	}

	return true;
}

bool _createMovieFromURL(string urlIn,  Movie &movie){
	char * url = (char *)urlIn.c_str();
	Handle urlDataRef;

	OSErr err;

	urlDataRef = NewHandle(strlen(url) + 1);
	if ( ( err = MemError()) != noErr){ ofLog(OF_LOG_ERROR,"createMovieFromURL: error creating url handle"); return false;}

	BlockMoveData(url, *urlDataRef, strlen(url) + 1);

	err = NewMovieFromDataRef(&movie, newMovieActive,nil, urlDataRef, URLDataHandlerSubType);
	DisposeHandle(urlDataRef);

	if(err != noErr){
		ofLog(OF_LOG_ERROR,"createMovieFromURL: error loading url");
		return false;
	}else{
		return true;
	}

	return false;
}

OSErr 	DrawCompleteProcXX(Movie theMovie, long refCon);

OSErr DrawCompleteProcXX(Movie theMovie, long refCon) {

	qbz::VideoPlayer * ofvp = (qbz::VideoPlayer *)refCon;
	#if defined(TARGET_OSX) && defined(__BIG_ENDIAN__)
		convertPixels(ofvp->offscreenGWorldPixels, ofvp->pixels, ofvp->width, ofvp->height);
	#endif

	ofvp->bHavePixelsChanged = true;
	if (ofvp->bUseTexture == true){
		ofvp->tex.loadData(ofvp->pixels, ofvp->width, ofvp->height, GL_RGB);
	}
	return noErr;
}



using namespace qbz;


VideoPlayer::VideoPlayer () {
	bLoaded = false;
	width = 0;
	height = 0;
	speed = 1;
	bUseTexture = false;
	bStarted = false;
	pixels = NULL;
	nFrames = 0;
	bPaused = false;
}

unsigned char* VideoPlayer::getPixels() {
	return pixels;
}

//------------------------------------
//for getting a reference to the texture
ofTexture & VideoPlayer::getTextureReference() {
	if(!tex.bAllocated() ){
		ofLog(OF_LOG_WARNING, "VideoPlayer - getTextureReference - texture is not allocated");
	}
	return tex;
}
int VideoPlayer::getTextureID(){
	if(!tex.bAllocated() ){
		ofLog(OF_LOG_WARNING, "VideoPlayer - getTextureReference - texture is not allocated");
	}
	return tex.texData.textureID;
}
bool VideoPlayer::isFrameNew() {
	return bIsFrameNew;
}

void VideoPlayer::update() {
	idleMovie();
}

void VideoPlayer::idleMovie() {
	if (bLoaded == true) {
		#if defined(TARGET_WIN32) || defined(QT_USE_MOVIETASK)
			MoviesTask(moviePtr,0);
		#endif
	}

	// ---------------------------------------------------
	// 		on all platforms,
	// 		do "new"ness ever time we idle...
	// 		before "isFrameNew" was clearning,
	// 		people had issues with that...
	// 		and it was badly named so now, newness happens
	// 		per-idle not per isNew call
	// ---------------------------------------------------
	
	if (bLoaded == true) {
		bIsFrameNew = bHavePixelsChanged;
		if (bHavePixelsChanged == true) {
			bHavePixelsChanged = false;
		}
	}
}

void VideoPlayer::closeMovie() {
	if (bLoaded == true) {
	    DisposeMovie (moviePtr);
		DisposeMovieDrawingCompleteUPP(myDrawCompleteProc);
		moviePtr = NULL;
    }
    bLoaded = false;
}

void VideoPlayer::close() {
	closeMovie();
}

VideoPlayer::~VideoPlayer() {
	closeMovie();
	if(allocated) delete[] pixels;
	if(allocated) delete[] offscreenGWorldPixels;
	if ((offscreenGWorld)) DisposeGWorld((offscreenGWorld));
	tex.clear();
}

void VideoPlayer::createImgMemAndGWorld() {
	Rect movieRect;
	movieRect.top = 0;
	movieRect.left = 0;
	movieRect.bottom = height;
	movieRect.right = width;
	offscreenGWorldPixels = new unsigned char[4 * width * height + 32];
	pixels = new unsigned char[width*height*3];

	#if defined(TARGET_OSX) && defined(__BIG_ENDIAN__)
		QTNewGWorldFromPtr (&(offscreenGWorld), k32ARGBPixelFormat, &(movieRect), NULL, NULL, 0, (offscreenGWorldPixels), 4 * width);		
	#else
		QTNewGWorldFromPtr (&(offscreenGWorld), k24RGBPixelFormat, &(movieRect), NULL, NULL, 0, (pixels), 3 * width);
	#endif

	LockPixels(GetGWorldPixMap(offscreenGWorld));
	SetGWorld (offscreenGWorld, NULL);
	SetMovieGWorld (moviePtr, offscreenGWorld, nil);
	//------------------------------------ texture stuff:
	if (bUseTexture){
		// create the texture, set the pixels to black and
		// upload them to the texture (so at least we see nothing black the callback)
		tex.allocate(width,height,GL_RGB);
		memset(pixels, 255, width*height*3);
		tex.loadData(pixels, width, height, GL_RGB);
		allocated = true;
	}
}

bool VideoPlayer::loadMovie(string name) {

	initializeQuicktime();
	bLoaded = false;
	
	if(!_createMovieFromPath((char *)name.c_str(), moviePtr)) return false;
		
	Rect movieRect;
	GetMovieBox(moviePtr, &(movieRect));
	width	= movieRect.right;
	height 	= movieRect.bottom;
	createImgMemAndGWorld();
	if (moviePtr == NULL){
		return false;
	}

	myDrawCompleteProc = NewMovieDrawingCompleteUPP (DrawCompleteProcXX);
	SetMovieDrawingCompleteProc (moviePtr, movieDrawingCallWhenChanged,  myDrawCompleteProc, (long)this);

	nFrames	= 0;
	TimeValue curMovieTime;
	curMovieTime = 0;
	TimeValue duration;
	OSType whichMediaType = FOUR_CHAR_CODE('vide');
	short flags = nextTimeMediaSample + nextTimeEdgeOK;
	
	while (curMovieTime >= 0) {
		nFrames++;
		GetMovieNextInterestingTime(moviePtr,flags,1,&whichMediaType,curMovieTime,0,&curMovieTime,&duration);
		flags = nextTimeMediaSample;
	}
	nFrames--; // there's an extra time step at the end of themovie

	GoToBeginningOfMovie(moviePtr);
	SetMovieActiveSegment(moviePtr, -1,-1);
	MoviesTask(moviePtr,0);

	#if defined(TARGET_OSX) && defined(__BIG_ENDIAN__)
		convertPixels(offscreenGWorldPixels, pixels, width, height);
	#endif

	if (bUseTexture == true){
		tex.loadData(pixels, width, height, GL_RGB);
	}

	bStarted 				= false;
	bLoaded 				= true;
	bPlaying 				= false;
	bHavePixelsChanged 		= false;
	speed 					= 1;
	return true;
}

void VideoPlayer::start() {
	if (bLoaded == true && bStarted == false){
		SetMovieActive(moviePtr, true);

		//------------------ set the movie rate to default
		//------------------ and preroll, so the first frames come correct

		TimeValue timeNow 	= 	GetMovieTime(moviePtr, 0);
		Fixed playRate 		=	GetMoviePreferredRate(moviePtr); 		//Not being used!

		PrerollMovie(moviePtr, timeNow, X2Fix(speed));
		SetMovieRate(moviePtr,  X2Fix(speed));
		setLoopState(OF_LOOP_NORMAL);

		// get some pixels in there right away:
		MoviesTask(moviePtr,0);
		#if defined(TARGET_OSX) && defined(__BIG_ENDIAN__)
			convertPixels(offscreenGWorldPixels, pixels, width, height);
		#endif
		bHavePixelsChanged = true;
		if (bUseTexture == true){
			tex.loadData(pixels, width, height, GL_RGB);
		}

		bStarted = true;
		bPlaying = true;
	}

}

void VideoPlayer::play() {
	if (!bStarted) {
	 	start();
	} else {
		// ------------ lower level "startMovie"
		// ------------ use desired speed & time (-1,1,etc) to Preroll...
		bPlaying = true;
		TimeValue timeNow;
	   	timeNow = GetMovieTime(moviePtr, nil);
		PrerollMovie(moviePtr, timeNow, X2Fix(speed));
		SetMovieRate(moviePtr,  X2Fix(speed));
		MoviesTask(moviePtr, 0);
	}
}

void VideoPlayer::stop() {
	StopMovie (moviePtr);
	SetMovieActive (moviePtr, false);
	bStarted = false;
}

void VideoPlayer::setVolume(int volume) {
	SetMovieVolume(moviePtr, volume);
}

void VideoPlayer::setLoopState(int state) {
		TimeBase myTimeBase;
		long myFlags = 0L;
		myTimeBase = GetMovieTimeBase(moviePtr);
		myFlags = GetTimeBaseFlags(myTimeBase);
		switch (state) {
			case OF_LOOP_NORMAL:
				myFlags |= loopTimeBase;
				myFlags &= ~palindromeLoopTimeBase;
				SetMoviePlayHints(moviePtr, hintsLoop, hintsLoop);
				SetMoviePlayHints(moviePtr, 0L, hintsPalindrome);
				break;
			case OF_LOOP_PALINDROME:
				myFlags |= loopTimeBase;
				myFlags |= palindromeLoopTimeBase;
				SetMoviePlayHints(moviePtr, hintsLoop, hintsLoop);
				SetMoviePlayHints(moviePtr, hintsPalindrome, hintsPalindrome);
				break;
			case OF_LOOP_NONE:
				default:
				myFlags &= ~loopTimeBase;
				myFlags &= ~palindromeLoopTimeBase;
				SetMoviePlayHints(moviePtr, 0L, hintsLoop |
				hintsPalindrome);
				break;
		}
		SetTimeBaseFlags(myTimeBase, myFlags);
}

void VideoPlayer::setPosition(float pct) {

	 	TimeRecord tr;
	 	tr.base 		= GetMovieTimeBase(moviePtr);
		long total 		= GetMovieDuration(moviePtr );
		long newPos 	= (long)((float)total * pct);
		SetMovieTimeValue(moviePtr, newPos);
		MoviesTask(moviePtr,0);
}

void VideoPlayer::setFrame(int frame){

	// frame 0 = first frame...

	// this is the simple way...
	//float durationPerFrame = getDuration() / getTotalNumFrames();

	// seems that freezing, doing this and unfreezing seems to work alot
	// better then just SetMovieTimeValue() ;

	if (!bPaused) SetMovieRate(moviePtr, X2Fix(0));

	// this is better with mpeg, etc:
	double frameRate = 0;
	double movieTimeScale = 0;
	MovieGetStaticFrameRate(moviePtr, &frameRate);
	movieTimeScale = GetMovieTimeScale(moviePtr);

	if (frameRate > 0){
		double frameDuration = 1 / frameRate;
		TimeValue t = (TimeValue)(frame * frameDuration * movieTimeScale);
		SetMovieTimeValue(moviePtr, t);
		MoviesTask(moviePtr, 0);
	}

   if (!bPaused) SetMovieRate(moviePtr, X2Fix(speed));
}

float VideoPlayer::getDuration() {
	return (float) (GetMovieDuration (moviePtr) / (double) GetMovieTimeScale (moviePtr));
}

float VideoPlayer::getPosition() {
		long total 		= GetMovieDuration(moviePtr);
		long current 	= GetMovieTime(moviePtr, nil);
		float pct 		= ((float)current/(float)total);
		return pct;
}

int VideoPlayer::getCurrentFrame() {
	int frame = 0;

	// zach I think this may fail on variable length frames...
	float pos = getPosition();


	float  framePosInFloat = ((float)getTotalNumFrames() * pos);
	int    framePosInInt = (int)framePosInFloat;
	float  floatRemainder = (framePosInFloat - framePosInInt);
	if (floatRemainder > 0.5f) framePosInInt = framePosInInt + 1;
	//frame = (int)ceil((getTotalNumFrames() * getPosition()));
	frame = framePosInInt;

	return frame;
}

bool VideoPlayer::getIsMovieDone() {
		bool bIsMovieDone = (bool)IsMovieDone(moviePtr);
		return bIsMovieDone;
}

void VideoPlayer::firstFrame() {
	setFrame(0);
}

void VideoPlayer::nextFrame() {
	setFrame(getCurrentFrame() + 1);
}

void VideoPlayer::previousFrame() {
	setFrame(getCurrentFrame() - 1);
}

void VideoPlayer::setSpeed(float _speed) {
	speed = _speed;
	if (bPlaying == true){
		//setMovieRate actually plays, so let's call it only when we are playing
		SetMovieRate(moviePtr, X2Fix(speed));
	}
}

float VideoPlayer::getSpeed() {
	return speed;
}

void VideoPlayer::setPaused(bool _bPause) {
	bPaused = _bPause;
		// there might be a more "quicktime-ish" way (or smarter way)
		// to do this for now, to pause, just set the movie's speed to zero,
		// on un-pause, set the movie's speed to "speed"
		// (and hope that speed != 0...)
		if (bPlaying == true){
			if (bPaused == true) 	SetMovieRate(moviePtr, X2Fix(0));
			else 					SetMovieRate(moviePtr, X2Fix(speed));
		}
}

//------------------------------------
void VideoPlayer::setUseTexture(bool bUse){
	bUseTexture = bUse;
}

void VideoPlayer::setAnchorPercent(float xPct, float yPct){
    if (bUseTexture)tex.setAnchorPercent(xPct, yPct);
}

void VideoPlayer::setAnchorPoint(int x, int y){
    if (bUseTexture)tex.setAnchorPoint(x, y);
}

void VideoPlayer::resetAnchor(){
   	if (bUseTexture)tex.resetAnchor();
}

void VideoPlayer::draw(float _x, float _y, float _w, float _h){
	if (bUseTexture) {
		tex.draw(_x, _y, _w, _h);
	}
}

void VideoPlayer::draw(float _x, float _y){
	draw(_x, _y, (float)width, (float)height);
}

int VideoPlayer::getTotalNumFrames(){
	return nFrames;
}

float VideoPlayer::getHeight(){
	return (float)height;
}
float VideoPlayer::getWidth(){
	return (float)width;
}
