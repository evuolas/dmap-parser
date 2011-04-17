#include "dmap_parser.h"
#include <stdint.h>

typedef enum DMAP_FIELD {
	DMAP_UNKNOWN,
	DMAP_INT,
	DMAP_STR,
	DMAP_DATE,
	DMAP_VERS,
	DMAP_DICT
} DMAP_FIELD;

typedef struct dmap_type {
	const uint32_t code;
	DMAP_FIELD type;
	const char* name;
} dmap_type;

static dmap_type dmap_types[] = {
	{ 'abal', DMAP_DICT, "daap.browsealbumlisting" },
	{ 'abar', DMAP_DICT, "daap.browseartistlisting" },
	{ 'abcp', DMAP_DICT, "daap.browsecomposerlisting" },
	{ 'abgn', DMAP_DICT, "daap.browsegenrelisting" },
	{ 'abpl', DMAP_INT,  "daap.baseplaylist" },
	{ 'abro', DMAP_DICT, "daap.databasebrowse" },
	{ 'adbs', DMAP_DICT, "daap.databasesongs" },
	{ 'aeAD', DMAP_DICT, "com.apple.itunes.adam.ids.array" },
	{ 'aeAI', DMAP_INT,  "com.apple.itunes.itms.artistid" },
	{ 'aeCI', DMAP_INT,  "com.apple.itunes.itms.composerid" },
	{ 'aeCR', DMAP_STR,  "com.apple.itunes.content.rating" } ,
	{ 'aeDP', DMAP_INT,  "com.apple.itunes.drm.platform.id" },
	{ 'aeDR', DMAP_INT,  "com.apple.itunes.drm.user.id" },
	{ 'aeDV', DMAP_INT,  "com.apple.itunes.drm.versions" },
	{ 'aeEN', DMAP_STR,  "com.apple.itunes.episode.num.str" },
	{ 'aeES', DMAP_INT,  "com.apple.itunes.episode.sort" },
	{ 'aeGD', DMAP_INT,  "com.apple.itunes.gapless.enc.dr" } ,
	{ 'aeGE', DMAP_INT,  "com.apple.itunes.gapless.enc.del" },
	{ 'aeGH', DMAP_INT,  "com.apple.itunes.gapless.heur" },
	{ 'aeGI', DMAP_INT,  "com.apple.itunes.itms.genreid" },
	{ 'aeGR', DMAP_INT,  "com.apple.itunes.gapless.resy" },
	{ 'aeGU', DMAP_INT,  "com.apple.itunes.gapless.dur" },
	{ 'aeHD', DMAP_INT,  "com.apple.itunes.is.hd.video" },
	{ 'aeHV', DMAP_INT,  "com.apple.itunes.has.video" },
	{ 'aeK1', DMAP_INT,  "com.apple.itunes.drm.key1.id" },
	{ 'aeK2', DMAP_INT,  "com.apple.itunes.drm.key2.id" },
	{ 'aeMK', DMAP_INT,  "com.apple.itunes.mediakind" },
	{ 'aeMk', DMAP_INT,  "com.apple.itunes.extended.media.kind" },
	{ 'aeND', DMAP_INT,  "com.apple.itunes.non.drm.user.id" },
	{ 'aeNN', DMAP_STR,  "com.apple.itunes.network.name" },
	{ 'aeNV', DMAP_INT,  "com.apple.itunes.norm.volume" },
	{ 'aePC', DMAP_INT,  "com.apple.itunes.is.podcast" },
	{ 'aePI', DMAP_INT,  "com.apple.itunes.itms.playlistid" },
	{ 'aePP', DMAP_INT,  "com.apple.itunes.is.podcast.playlist" },
	{ 'aePS', DMAP_INT,  "com.apple.itunes.special.playlist" },
	{ 'aeSE', DMAP_INT,  "com.apple.itunes.store.pers.id" },
	{ 'aeSF', DMAP_INT,  "com.apple.itunes.itms.storefrontid" },
	{ 'aeSG', DMAP_INT,  "com.apple.itunes.saved.genius" },
	{ 'aeSI', DMAP_INT,  "com.apple.itunes.itms.songid" },
	{ 'aeSN', DMAP_STR,  "com.apple.itunes.series.name" },
	{ 'aeSP', DMAP_INT,  "com.apple.itunes.smart.playlist" },
	{ 'aeSU', DMAP_INT,  "com.apple.itunes.season.num" },
	{ 'aeSV', DMAP_INT,  "com.apple.itunes.music.sharing.version" },
	{ 'aeXD', DMAP_STR,  "com.apple.itunes.xid" },
	{ 'agrp', DMAP_STR,  "daap.songgrouping" },
	{ 'aply', DMAP_DICT, "daap.databaseplaylists" },
	{ 'aprm', DMAP_INT,  "daap.playlistrepeatmode" },
	{ 'apro', DMAP_VERS, "daap.protocolversion" },
	{ 'apsm', DMAP_INT,  "daap.playlistshufflemode" },
	{ 'apso', DMAP_DICT, "daap.playlistsongs" },
	{ 'arif', DMAP_DICT, "daap.resolveinfo" },
	{ 'arsv', DMAP_DICT, "daap.resolve" },
	{ 'asaa', DMAP_STR,  "daap.songalbumartist" },
	{ 'asai', DMAP_INT,  "daap.songalbumid" },
	{ 'asal', DMAP_STR,  "daap.songalbum" },
	{ 'asar', DMAP_STR,  "daap.songartist" },
	{ 'asbk', DMAP_INT,  "daap.bookmarkable" },
	{ 'asbo', DMAP_INT,  "daap.songbookmark" },
	{ 'asbr', DMAP_INT,  "daap.songbitrate" },
	{ 'asbt', DMAP_INT,  "daap.songbeatsperminute" },
	{ 'ascd', DMAP_INT,  "daap.songcodectype" },
	{ 'ascm', DMAP_STR,  "daap.songcomment" },
	{ 'ascn', DMAP_STR,  "daap.songcontentdescription" },
	{ 'asco', DMAP_INT,  "daap.songcompilation" },
	{ 'ascp', DMAP_STR,  "daap.songcomposer" },
	{ 'ascr', DMAP_INT,  "daap.songcontentrating" },
	{ 'ascs', DMAP_INT,  "daap.songcodecsubtype" },
	{ 'asct', DMAP_STR,  "daap.songcategory" },
	{ 'asda', DMAP_DATE, "daap.songdateadded" },
	{ 'asdb', DMAP_INT,  "daap.songdisabled" },
	{ 'asdc', DMAP_INT,  "daap.songdisccount" },
	{ 'asdk', DMAP_INT,  "daap.songdatakind" },
	{ 'asdm', DMAP_DATE, "daap.songdatemodified" },
	{ 'asdn', DMAP_INT,  "daap.songdiscnumber" },
	{ 'asdp', DMAP_DATE, "daap.songdatepurchased" },
	{ 'asdr', DMAP_DATE, "daap.songdatereleased" },
	{ 'asdt', DMAP_STR,  "daap.songdescription" },
	{ 'ased', DMAP_INT,  "daap.songextradata" },
	{ 'aseq', DMAP_STR,  "daap.songeqpreset" },
	{ 'asfm', DMAP_STR,  "daap.songformat" },
	{ 'asgn', DMAP_STR,  "daap.songgenre" },
	{ 'asgp', DMAP_INT,  "daap.songgapless" },
	{ 'ashp', DMAP_INT,  "daap.songhasbeenplayed" },
	{ 'asky', DMAP_STR,  "daap.songkeywords" },
	{ 'aslc', DMAP_STR,  "daap.songlongcontentdescription" },
	{ 'asls', DMAP_INT,  "daap.songlongsize" },
	{ 'aspu', DMAP_STR,  "daap.songpodcasturl" },
	{ 'asrv', DMAP_INT,  "daap.songrelativevolume" },
	{ 'assa', DMAP_STR,  "daap.sortartist" },
	{ 'assc', DMAP_STR,  "daap.sortcomposer" },
	{ 'assl', DMAP_STR,  "daap.sortalbumartist" },
	{ 'assn', DMAP_STR,  "daap.sortname" },
	{ 'assp', DMAP_INT,  "daap.songstoptime" },
	{ 'assr', DMAP_INT,  "daap.songsamplerate" },
	{ 'asss', DMAP_STR,  "daap.sortseriesname" },
	{ 'asst', DMAP_INT,  "daap.songstarttime" },
	{ 'assu', DMAP_STR,  "daap.sortalbum" },
	{ 'assz', DMAP_INT,  "daap.songsize" },
	{ 'astc', DMAP_INT,  "daap.songtrackcount" },
	{ 'astm', DMAP_INT,  "daap.songtime" },
	{ 'astn', DMAP_INT,  "daap.songtracknumber" },
	{ 'asul', DMAP_STR,  "daap.songdataurl" },
	{ 'asur', DMAP_INT,  "daap.songuserrating" },
	{ 'asyr', DMAP_INT,  "daap.songyear" },
	{ 'ated', DMAP_INT,  "daap.supportsextradata" },
	{ 'avdb', DMAP_DICT, "daap.serverdatabases" },
	{ 'caar', DMAP_INT,  "dacp.availablerepeatstates" }, /* some kind of ORed list? 1=disabled, 6=repeat all & repeat one enabled */
	{ 'caas', DMAP_INT,  "dacp.availablshufflestates" }, /* some kind of ORed list? 1=disabled, 2=enabled */
	{ 'caci', DMAP_DICT, "caci" },
	{ 'cana', DMAP_STR,  "dacp.nowplayingartist" },
	{ 'cang', DMAP_STR,  "dacp.nowplayinggenre" },
	{ 'canl', DMAP_STR,  "dacp.nowplayingalbum" },
	{ 'cann', DMAP_STR,  "dacp.nowplayingname" },
	{ 'caps', DMAP_INT,  "dacp.playerstate" },
	{ 'carp', DMAP_INT,  "dacp.repeatstate" },
	{ 'cash', DMAP_INT,  "dacp.shufflestate" },
	{ 'casp', DMAP_DICT, "dacp.speakers" },
	{ 'cavc', DMAP_INT,  "dmcp.volumecontrollable" }, /* Should this be cavc? Was cmvc */
	{ 'ceJC', DMAP_INT,  "com.apple.itunes.jukebox.client.vote" },
	{ 'ceJI', DMAP_INT,  "com.apple.itunes.jukebox.current" },
	{ 'ceJS', DMAP_INT,  "com.apple.itunes.jukebox.score" },
	{ 'ceJV', DMAP_INT,  "com.apple.itunes.jukebox.vote" },
	{ 'cmgt', DMAP_DICT, "dmcp.getpropertyresponse" },
	{ 'cmsr', DMAP_INT,  "dmcp.revisionid" },
	{ 'cmst', DMAP_DICT, "dmcp.playstatus" },
	{ 'cmvo', DMAP_INT,  "dmcp.volume" },
	{ 'mbcl', DMAP_DICT, "dmap.bag" },
	{ 'mccr', DMAP_DICT, "dmap.contentcodesresponse" },
	{ 'mcna', DMAP_STR,  "dmap.contentcodesname" },
	{ 'mcnm', DMAP_INT,  "dmap.contentcodesnumber" },
	{ 'mcon', DMAP_DICT, "dmap.container" },
	{ 'mctc', DMAP_INT,  "dmap.containercount" },
	{ 'mcti', DMAP_INT,  "dmap.containeritemid" },
	{ 'mcty', DMAP_INT,  "dmap.contentcodestype" },
	{ 'mdcl', DMAP_DICT, "dmap.dictionary" },
	{ 'meds', DMAP_INT,  "dmap.editcommandssupported" },
	{ 'miid', DMAP_INT,  "dmap.itemid" },
	{ 'mikd', DMAP_INT,  "dmap.itemkind" },
	{ 'mimc', DMAP_INT,  "dmap.itemcount" },
	{ 'minm', DMAP_STR,  "dmap.itemname" },
	{ 'minm', DMAP_STR,  "dmap.itemname" },
	{ 'mlcl', DMAP_DICT, "dmap.listing" },
	{ 'mlid', DMAP_INT,  "dmap.sessionid" },
	{ 'mlit', DMAP_DICT, "dmap.listingitem" },
	{ 'mlog', DMAP_DICT, "dmap.loginresponse" },
	{ 'mpco', DMAP_INT,  "dmap.parentcontainerid" },
	{ 'mper', DMAP_INT,  "dmap.persistentid" },
	{ 'mpro', DMAP_VERS, "dmap.protocolversion" },
	{ 'mrco', DMAP_INT,  "dmap.returnedcount" },
	{ 'msal', DMAP_INT,  "dmap.supportsautologout" },
	{ 'msas', DMAP_INT,  "dmap.authenticationschemes" },
	{ 'msau', DMAP_INT,  "dmap.authenticationmethod" },
	{ 'msbr', DMAP_INT,  "dmap.supportsbrowse" },
	{ 'msdc', DMAP_INT,  "dmap.databasescount" },
	{ 'msex', DMAP_INT,  "dmap.supportsextensions" },
	{ 'msix', DMAP_INT,  "dmap.supportsindex" },
	{ 'mslr', DMAP_INT,  "dmap.loginrequired" },
	{ 'msma', DMAP_INT,  "dmap.macaddress" },
	{ 'msml', DMAP_DICT, "msml" },
	{ 'mspi', DMAP_INT,  "dmap.supportspersistentids" },
	{ 'msqy', DMAP_INT,  "dmap.supportsquery" },
	{ 'msrs', DMAP_INT,  "dmap.supportsresolve" },
	{ 'msrv', DMAP_DICT, "dmap.serverinforesponse" },
	{ 'mstc', DMAP_DATE, "dmap.utctime" },
	{ 'mstm', DMAP_INT,  "dmap.timeoutinterval" },
	{ 'msto', DMAP_INT,  "dmap.utcoffset" },
	{ 'msts', DMAP_STR,  "dmap.statusstring" },
	{ 'mstt', DMAP_INT,  "dmap.status" },
	{ 'msup', DMAP_INT,  "dmap.supportsupdate" },
	{ 'mtco', DMAP_INT,  "dmap.specifiedtotalcount" },
	{ 'mudl', DMAP_DICT, "dmap.deletedidlisting" },
	{ 'mupd', DMAP_DICT, "dmap.updateresponse" },
	{ 'musr', DMAP_INT,  "dmap.serverrevision" },
	{ 'muty', DMAP_INT,  "dmap.updatetype" },
	{ 0, 0, 0 }
};

dmap_type* dmap_type_from_code(uint32_t code) {
	dmap_type* t = dmap_types;
	while (t->code != 0) {
		if (t->code == code) {
			return t;
		}
		t++;
	}

	return 0;
}

int32_t dmap_read_i32(const char *buf)
{
	return ((buf[0] & 0xff) << 24) |
    ((buf[1] & 0xff) << 16) |
    ((buf[2] & 0xff) <<  8) |
    ((buf[3] & 0xff));
}

int dmap_parse(const char* buf, int len) {
	uint32_t code = 0;
	uint32_t field_len = 0;
	char field_type;
	dmap_type *t = 0;
	const char *p = buf;
	const char *end = buf + len;

	while (end - p >= 8) {
		code = dmap_read_i32(p);
		t = dmap_type_from_code(code);
		p += 4;

		field_len = dmap_read_i32(p);
		p += 4;

		if (!t) {
			// make a best guess of the type
			field_type = DMAP_UNKNOWN;
		} else {
			field_type = t->type;
		}

		switch (field_type) {
			case DMAP_INT:
				// Determine the integer's type based on its size
				switch (field_len) {
					case 1:
						break;
					case 4:
					{
						//int test_int = dmap_read_i32(p);
						break;
					}
				}
				break;
			case DMAP_DICT:
				dmap_parse(p, field_len);
				break;
		}

		p += field_len;
	}

	return 0;
}
