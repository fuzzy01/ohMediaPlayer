#include <OhNetTypes.h>
#include <Core/DvDevice.h>
#include <OhNet.h>
#include <Ascii.h>
#include <Stack.h>
#include <Maths.h>
#include <OptionParser.h>
#include "OpenHome/Product.h"
#include "OpenHome/Playlist.h"

#ifdef _WIN32

#define CDECL __cdecl

#else

#define CDECL

#endif

using namespace OpenHome;
using namespace OpenHome::MediaPlayer;
using namespace OpenHome::TestFramework;

static const TUint kTracksMax = 1000;
static const Brn kProtocolInfo("http-get:*:audio/x-flac:*,http-get:*:audio/wav:*,http-get:*:audio/wave:*,http-get:*:audio/x-wav:*,http-get:*:audio/mpeg:*,http-get:*:audio/x-mpeg:*,http-get:*:audio/mp1:*,http-get:*:audio/aiff:*,http-get:*:audio/x-aiff:*,http-get:*:audio/x-m4a:*,http-get:*:audio/x-ms-wma:*,rtsp-rtp-udp:*:audio/x-ms-wma:*,http-get:*:audio/x-scpls:*,http-get:*:audio/x-mpegurl:*,http-get:*:audio/x-ms-asf:*,http-get:*:audio/x-ms-wax:*,http-get:*:audio/x-ms-wvx:*,http-get:*:video/x-ms-asf:*,http-get:*:video/x-ms-wax:*,http-get:*:video/x-ms-wvx:*,http-get:*:text/xml:*,http-get:*:audio/aac:*,http-get:*:audio/aacp:*,http-get:*:audio/mp4:*,http-get:*:audio/ogg:*,http-get:*:audio/x-ogg:*,http-get:*:application/ogg:*");

class StandbyHandler : public IStandbyHandler
{
public: 
    virtual void SetStandby(TBool aValue);
};

void StandbyHandler::SetStandby(TBool aValue)
{
    printf("Setting Standby: %d\n", aValue);
}

class SourceIndexHandler : public ISourceIndexHandler
{
public:
    virtual void SetSourceIndex(TUint aValue);
};

void SourceIndexHandler::SetSourceIndex(TUint aValue)
{
    printf("Setting source: %d\n", aValue);
}

int CDECL main(int aArgc, char* aArgv[])
{
    Net::InitialisationParams* initParams = Net::InitialisationParams::Create();

    Net::UpnpLibrary::Initialise(initParams);
    
    Net::UpnpLibrary::StartDv();

	Bwh udn("device");

    Net::DvDeviceStandard* device = new Net::DvDeviceStandard(udn);

    SourceIndexHandler* sourceIndexHandler = new SourceIndexHandler();
    StandbyHandler* standbyHandler = new StandbyHandler();

    ProductImpl* productImpl = new ProductImpl(*device, 
        *standbyHandler, 
        *sourceIndexHandler, 
        true,
        "",
        "OpenHome",
        "OpenHome Consortium",
        "http://openhome.org",
        "",
        "OpenHome Media Player",
        "",
        "",
        "",
        "OpenHomeKeith",
        "OpenHome Media Player",
        "",
        "",
        "");

    
    device->SetAttribute("Upnp.Domain", "av.openhome.org");
    device->SetAttribute("Upnp.Type", "MediaPlayer");
    device->SetAttribute("Upnp.Version", "1");
    device->SetAttribute("Upnp.FriendlyName", "ohMediaPlayer");
    device->SetAttribute("Upnp.Manufacturer", "OpenHome");
    device->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.ModelDescription", "OpenHome MediaPlayer");
    device->SetAttribute("Upnp.ModelName", "OpenHome MediaPlayer");
    device->SetAttribute("Upnp.ModelNumber", "1");
    device->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    device->SetAttribute("Upnp.SerialNumber", "");
    device->SetAttribute("Upnp.Upc", "");

    PlaylistImpl* playlistImpl = new PlaylistImpl(*device, kTracksMax, kProtocolInfo);

    device->SetEnabled();

    (void)productImpl;
    (void)playlistImpl;

    while(1) {}

    delete (device);
    
	printf("\n");
	
    return (0);
}
