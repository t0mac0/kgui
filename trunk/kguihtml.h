#ifndef __KGUIHTML__
#define __KGUIHTML__

/* todo: fix print to use new 'page', also allow open link in 'new tab' and multiple page tabs */

/*! @defgroup kGUIHTMLObjects kGUIHTMLObjects */ 

#include "kguixml.h"
#include "kguidl.h"
#include "kguireq.h"

/*! @class kGUIHTMLPluginObj
	@brief plugin wrapper class for viewing movies and other external items like pdf files etc
    @ingroup kGUIHTMLObjects */
class kGUIHTMLPluginObj : public kGUIContainerObj
{
public:
	kGUIHTMLPluginObj() {}
	virtual ~kGUIHTMLPluginObj() {}
	virtual kGUIHTMLPluginObj *New(void)=0;	/* generate a new one */
	virtual DataHandle *GetDH(void)=0;		/* used to attach data source */
	virtual bool Open(void)=0;				/* called after attaching datahandle, true=valid, false=invalid */
	virtual kGUIObj *GetObj(void)=0;		/* object used to attach event handle to */
private:
};

/* this is used for the css priority, definiting where the css style originated */
enum
{
OWNER_SYS,
OWNER_USER,
OWNER_AUTHOR,
OWNER_AUTHORIMPORTANT,
OWNER_USERIMPORTANT,
OWNER_NUM
};

/*! @internal @struct TAGLIST_DEF
	@brief Internal struct used by the kGUIHTMLPageObj class.
	Structure defining HTML tags names and their associated information */
typedef struct
{
	bool noclose;
	bool endoptional;
	const char *name;
	unsigned int tokenid;
	unsigned int defdisp;
}TAGLIST_DEF;

enum
{
HTMLTAG_A,
HTMLTAG_ABBR,
HTMLTAG_ACRONYM,
HTMLTAG_ADDRESS,
HTMLTAG_AREA,
HTMLTAG_B,
HTMLTAG_BASE,
HTMLTAG_BDO,
HTMLTAG_BIG,
HTMLTAG_BLINK,
HTMLTAG_BLOCKQUOTE,
HTMLTAG_BODY,
HTMLTAG_BR,
HTMLTAG_BUTTON,
HTMLTAG_CAPTION,
HTMLTAG_CENTER,
HTMLTAG_CITE,
HTMLTAG_CODE,
HTMLTAG_COL,
HTMLTAG_COLGROUP,
HTMLTAG_DD,
HTMLTAG_DEL,
HTMLTAG_DFN,
HTMLTAG_DIV,
HTMLTAG_DL,
HTMLTAG_DOCTYPE,
HTMLTAG_DT,
HTMLTAG_EM,
HTMLTAG_FIELDSET,
HTMLTAG_FONT,
HTMLTAG_FORM,
HTMLTAG_FRAME,
HTMLTAG_FRAMESET,
HTMLTAG_H1,
HTMLTAG_H2,
HTMLTAG_H3,
HTMLTAG_H4,
HTMLTAG_H5,
HTMLTAG_H6,
HTMLTAG_HEAD,
HTMLTAG_HR,
HTMLTAG_HTML,
HTMLTAG_I,
HTMLTAG_IFRAME,
HTMLTAG_IMG,
HTMLTAG_INPUT,
HTMLTAG_INS,

HTMLTAG_KBD,
HTMLTAG_LABEL,
HTMLTAG_LEGEND,
HTMLTAG_LI,
HTMLTAG_LINK,
HTMLTAG_MAP,
HTMLTAG_META,
HTMLTAG_NOBR,
HTMLTAG_NOFRAMES,
HTMLTAG_NOSCRIPT,
HTMLTAG_OBJECT,
HTMLTAG_OL,
HTMLTAG_OPTGROUP,
HTMLTAG_OPTION,
HTMLTAG_P,
HTMLTAG_PARAM,
HTMLTAG_PRE,
HTMLTAG_Q,
HTMLTAG_SAMP,
HTMLTAG_SCRIPT,
HTMLTAG_SELECT,
HTMLTAG_SMALL,
HTMLTAG_SPAN,
HTMLTAG_STRIKE,
HTMLTAG_STRONG,
HTMLTAG_STYLE,
HTMLTAG_SUB,
HTMLTAG_SUP,
HTMLTAG_TABLE,
HTMLTAG_TBODY,
HTMLTAG_THEAD,
HTMLTAG_TFOOT,
HTMLTAG_TD,
HTMLTAG_TEXTAREA,
HTMLTAG_TH,
HTMLTAG_TITLE,
HTMLTAG_TR,
HTMLTAG_TT,
HTMLTAG_U,
HTMLTAG_UL,
HTMLTAG_VAR,
HTMLTAG_WBR,
HTMLTAG_XML,

HTMLTAG_IMBEDTEXTGROUP,			/* used for inline text before whilespare rule applied */
HTMLTAG_IMBEDTEXT,				/* individual words after whitespace applied */
HTMLTAG_CONTENTGROUP,			/* internal used for before and after groups */
HTMLTAG_UNKNOWN,

/* these are internal types */
HTMLTAG_SINGLEOBJ,
HTMLTAG_ALL,		/* used for style selectors that apply to all '*' */
HTMLTAG_ROOT,		/* internal root object */
HTMLTAG_LIIMG,
HTMLTAG_LISHAPE,	/* disc,circle,square */

HTMLTAG_NUMTAGS
};

enum
{
HTMLSUBTAG_UNDEFINED,
HTMLSUBTAG_INPUTBUTTON,
HTMLSUBTAG_INPUTBUTTONSUBMIT,
HTMLSUBTAG_INPUTBUTTONRESET,
HTMLSUBTAG_INPUTBUTTONIMAGE,
HTMLSUBTAG_INPUTHIDDEN,
HTMLSUBTAG_INPUTCHECKBOX,
HTMLSUBTAG_INPUTRADIO,
HTMLSUBTAG_INPUTTEXTBOX,
HTMLSUBTAG_INPUTFILE,
HTMLSUBTAG_INPUTLISTBOX	/* parent id=select */
};

enum
{
TEXTDECORATION_NONE=0,
TEXTDECORATION_UNDERLINE=1,
TEXTDECORATION_OVERLINE=2,
TEXTDECORATION_LINETHROUGH=4,
TEXTDECORATION_BLINK=8
};

enum
{
TEXTTRANSFORM_NONE,
TEXTTRANSFORM_CAPITALIZE,
TEXTTRANSFORM_UPPERCASE,
TEXTTRANSFORM_LOWERCASE
};

/* draw settings */

enum
{
	MODE_MINMAX,
	MODE_POSITION,
};

enum
{
UNITS_PIXELS,
UNITS_CM,
UNITS_POINTS,
UNITS_EM,
UNITS_PERCENT,
UNITS_AUTO,
UNITS_UNDEFINED
};

/*! @internal @class kGUIUnits
	@brief Internal class used by the kGUIHTMLPageObj class.
	Class for CSS Units, px, cm, mm, % etc. 
    @ingroup kGUIHTMLObjects */
class kGUIUnits
{
public:
	kGUIUnits() {m_units=UNITS_UNDEFINED;m_vint=true;m_value.i=0;}
	void Set(kGUIString *s);
	void CopyFrom(kGUIUnits *from) {m_units=from->m_units;m_vint=from->m_vint;m_value.i=from->m_value.i;}
	bool GetIsFixed(void) {return ((m_units==UNITS_PIXELS) || (m_units==UNITS_POINTS) || (m_units==UNITS_EM) || (m_units==UNITS_CM));}
	void SetUnitType(int u) {m_units=u;}
	int GetUnitType(void) {return m_units;}
	void SetUnitValue(int v) {m_value.i=v;m_vint=true;}
	void SetUnitValue(double v) {m_value.d=v;m_vint=false;}
	int GetUnitValue(void) {return m_vint==true?m_value.i:(int)m_value.d;}
	double GetUnitValueD(void) {return m_vint==true?(double)m_value.i:m_value.d;}
	int CalcUnitValue(int scale100,int ems);
	double CalcUnitValue(double scale100,double ems);
	void Reset(void);
	void Zero(void) {m_units=UNITS_PIXELS;m_vint=true;m_value.i=0;}
private:
	unsigned int m_units:3;
	bool m_vint:1;
	union{
		double d;
		int i;
	}m_value;
};


class kGUIHTMLPageObj;
class kGUIHTMLObj;

/*! @internal @class kGUIHTMLLinkObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	Url link object class, for clickable links
    @ingroup kGUIHTMLObjects */
class kGUIHTMLLinkObj
{
public:
	kGUIHTMLLinkObj() {m_hover=false;m_page=0;m_a=0;m_hashover=false;}
	kGUIHTMLLinkObj(kGUIHTMLPageObj *page,kGUIHTMLObj *a) {m_hover=false;m_page=page;m_a=a;m_hashover=false;}
	void SetA(kGUIHTMLObj *a) {m_a=a;}
	void SetPage(kGUIHTMLPageObj *page) {m_page=page;}
	void SetURL(kGUIString *url) {m_url.SetString(url);}
	void SetReferrer(kGUIString *referrer) {m_referrer.SetString(referrer);}
	kGUIString *GetURL(void) {return &m_url;}
	kGUIString *GetReferrer(void) {return &m_referrer;}
	void SetOver(void);
	void SetHover(bool h) {m_hover=h;}
	bool GetHover(void) {return m_hover;}
	bool GetVisited(void);
	void Click(void);
private:
	kGUIHTMLPageObj *m_page;
	kGUIHTMLObj *m_a;
	kGUIString m_url;
	kGUIString m_referrer;
	bool m_hover:1;
	bool m_hashover;
};

/*! @internal @class kGUIHTMLTextObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML static text
    @ingroup kGUIHTMLObjects */
class kGUIHTMLTextObj : public kGUITextObj
{
public:
	kGUIHTMLTextObj() {m_fixedem=0;m_draw=true;SetOffsets(0,0);m_textdecoration=TEXTDECORATION_NONE;m_textdecorationcolor=DrawColor(0,0,0);m_plusspace=false;m_pluscr=false;m_link=0;}
	void Draw(void);
	bool UpdateInput(void);
	void SetLink(kGUIHTMLLinkObj *link) {m_link=link;}
	void SetTextDecoration(int d) {m_textdecoration=d;}
	void SetTextDecorationColor(kGUIColor c) {m_textdecorationcolor=c;}
	unsigned int GetTextDecoration(void) {return m_textdecoration;}
	kGUIColor GetTextDecorationColor(void) {return m_textdecorationcolor;}
	void SetShadow(int shadowr,int shadowx,int shadowy,kGUIColor shadowcolor) {m_shadowr=shadowr;m_shadowx=shadowx;m_shadowy=shadowy;m_shadowcolor=shadowcolor;}
	void SetFixedWidth(int em) {m_fixedem=em;}
	unsigned int GetFixedWidth(void) {return m_fixedem;}
	void SetPlusSpace(bool ps) {m_plusspace=ps;}
	bool GetPlusSpace(void) {return m_plusspace;}
	void SetPlusCR(bool ps) {m_pluscr=ps;}		/* true is string was split in PRE mode */
	bool GetPlusCR(void) {return m_pluscr;}
	void Blink(void) {if(m_draw)m_draw=false;else m_draw=true;Dirty();}
private:
	bool m_plusspace:1;
	bool m_pluscr:1;
	bool m_draw:1;		/* blink */
	unsigned int m_fixedem:8;
	unsigned int m_textdecoration:8;
	int m_shadowr:8;
	int m_shadowx:8;
	int m_shadowy:8;
	kGUIColor m_shadowcolor;
	kGUIColor m_textdecorationcolor;
	kGUIHTMLLinkObj *m_link;
};

enum
{
WHITESPACE_UNDEFINED,
WHITESPACE_NORMAL,
WHITESPACE_NOWRAP,
WHITESPACE_PRE,
WHITESPACE_PREWRAP,
WHITESPACE_PRELINE,
};

/*! @internal @class kGUIHTMLTextGroup
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML static text group, this contains text before whitespace and transform rules have been applied
    @ingroup kGUIHTMLObjects */
class kGUIHTMLTextGroup : public kGUIString
{
public:
	kGUIHTMLTextGroup(kGUIHTMLPageObj *page) {m_page=page;m_lastwhitespace=WHITESPACE_UNDEFINED;m_lasttransform=TEXTTRANSFORM_NONE;m_numchunks=0;m_chunks.Init(16,16);}
	void Split(unsigned int whitespace,unsigned int transform,kGUIHTMLObj *renderparent,kGUIHTMLObj *parent);
	unsigned int GetLastWhitespace(void) {return m_lastwhitespace;}
	unsigned int GetLastTransform(void) {return m_lasttransform;}
	unsigned int GetNumChildren(void) {return m_numchunks;}
private:
	unsigned int m_lastwhitespace:2;
	unsigned int m_lasttransform:2;

	unsigned int m_numchunks;
	kGUIHTMLPageObj *m_page;
	kGUIString m_tempstring;
	Array<kGUIHTMLObj *>m_chunks;
};

/*! @internal @class kGUIHTMLContentGroup
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML content group, this contains before and after content before it is processed into text / images etc
    @ingroup kGUIHTMLObjects */
class kGUIHTMLContentGroup : public kGUIReadString
{
public:
	kGUIHTMLContentGroup(kGUIHTMLPageObj *page) {m_changed=false;m_page=page;m_numchunks=0;m_chunks.Init(16,16);}
	void Split(kGUIHTMLObj *renderparent,kGUIHTMLObj *parent);
	bool GetChanged(void) {return m_changed;}
	void SetChanged(bool c) {m_changed=c;}
private:
	bool m_changed:1;
	unsigned int m_numchunks;
	kGUIHTMLPageObj *m_page;
	Array<kGUIHTMLObj *>m_chunks;
};

enum
{
LISTSTYLE_NONE,
LISTSTYLE_DISC,
LISTSTYLE_CIRCLE,
LISTSTYLE_SQUARE,
LISTSTYLE_DECIMAL,
LISTSTYLE_DECIMAL_LEADING_ZERO,
LISTSTYLE_LOWER_ROMAN,
LISTSTYLE_UPPER_ROMAN,
LISTSTYLE_LOWER_ALPHA,
LISTSTYLE_UPPER_ALPHA,
LISTSTYLE_LOWER_GREEK,
LISTSTYLE_IMAGE};

enum
{
LISTSTYLE_INSIDE,
LISTSTYLE_OUTSIDE};

/*! @internal @class kGUIHTMLLIPrefix
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML list prefix for inserting list text
    @ingroup kGUIHTMLObjects */
class kGUIHTMLLIPrefix
{
public:
	kGUIHTMLLIPrefix(kGUIHTMLPageObj *page) {m_position=0;m_style=LISTSTYLE_NONE;m_page=page;m_numchunks=0;m_chunks.Init(4,4);}
	void Purge(void);
	void SetIndex(unsigned int index) {m_index=index;}
	void Set(unsigned int style,unsigned int position,unsigned int urlid,unsigned int urlrefererid,kGUIHTMLObj *renderparent,kGUIHTMLObj *parent);
	unsigned int GetStyle(void) {return m_style;}
	unsigned int GetPosition(void) {return m_position;}
	unsigned int GetUrlID(void) {return m_urlid;}
private:
	unsigned int m_style:8;
	unsigned int m_position:1;
	unsigned int m_index;
	unsigned int m_urlid;
	unsigned int m_urlrefererid;
	unsigned int m_numchunks;
	kGUIHTMLPageObj *m_page;
	kGUIHTMLObj *m_renderparent;
	kGUIString m_tempstring;
	Array<kGUIHTMLObj *>m_chunks;
};

/*! @internal @class kGUIHTMLShapeObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML list prefix for inserting a list image
    @ingroup kGUIHTMLObjects */
class kGUIHTMLShapeObj: public kGUIObj
{
public:
	kGUIHTMLShapeObj() {m_type=0;}
	~kGUIHTMLShapeObj() {}
	void Draw(void);
	bool UpdateInput(void) {return false;}
	void SetType(unsigned int t) {m_type=t;}
private:
	unsigned int m_type;
};

/*! @internal @class kGUIHTMLButtonTextObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML text button object for use in forms
    @ingroup kGUIHTMLObjects */
class kGUIHTMLButtonTextObj : public kGUIHTMLTextObj
{
public:
	kGUIHTMLButtonTextObj() {m_styleparent=0;m_type=0;}
	kGUIHTMLButtonTextObj(kGUIHTMLObj *styleparent,int type) {m_styleparent=styleparent;m_type=type;}
	bool UpdateInput(void);
	void Draw(void);
private:
	unsigned int m_type;	/* HTMLCONST_SUBMIT, HTMLCONST_RESET, HTMLCONST_BUTTON */
	kGUIHTMLObj *m_styleparent;
};

/*! @internal @class kGUIHTMLInputBoxObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML inputbox object for use in forms
    @ingroup kGUIHTMLObjects */
class kGUIHTMLInputBoxObj : public kGUIInputBoxObj
{
public:
	kGUIHTMLInputBoxObj() {m_textdecoration=TEXTDECORATION_NONE;m_textdecorationcolor=DrawColor(0,0,0);}
	void SetTextDecoration(int d) {m_textdecoration=d;}
	void SetTextDecorationColor(kGUIColor c) {m_textdecorationcolor=c;}
	kGUIColor GetTextDecorationColor(void) {return m_textdecorationcolor;}
private:
	int m_textdecoration;
	kGUIColor m_textdecorationcolor;
};

enum
{
FORMMODE_GET,
FORMMODE_POST
};

/*! @internal @class kGUIHTMLFormObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML form object, contains all form elements like inputboxes, buttons, etc.
    @ingroup kGUIHTMLObjects */
class kGUIHTMLFormObj
{
public:
	kGUIHTMLFormObj() {m_mode=FORMMODE_GET;m_numchildren=0;m_children.Init(32,32);}
	void SetPage(class kGUIHTMLPageObj *page) {m_page=page;}
	kGUIString *GetReferrer(void) {return &m_referrer;}
	void SetName(kGUIString *n) {m_name.SetString(n);}
	kGUIString *GetName(void) {return &m_name;}
	void SetReferrer(kGUIString *referrer) {m_referrer.SetString(referrer);}
	void AddObject(kGUIHTMLObj *obj) {m_children.SetEntry(m_numchildren++,obj);}
	void SetAction(kGUIString *action) {m_action.SetString(action);}
	void SetMode(unsigned int mode) {m_mode=mode;}
	void Submit(kGUIHTMLObj *button);
	void CheckSimpleSubmit(void);
	void Reset(void);
	void Encode(kGUIString *in,kGUIString *out);
	unsigned int GetNumChildren(void) {return m_numchildren;}
	kGUIHTMLObj *GetChild(unsigned int index) {return m_children.GetEntry(index);}
private:
	unsigned int m_numchildren;
	unsigned int m_mode;
	kGUIString m_referrer;
	Array<kGUIHTMLObj *>m_children;
	kGUIString m_action;	/* URL when submitted */
	kGUIString m_name;		/* only used by Load/Save in go-back and go-forward in the browser */
	class kGUIHTMLPageObj *m_page;
};

class kGUIStyleObj;
class kGUIHTMLTableInfo;

/*! HTML color, contains RGB color or transparent
    @ingroup kGUIHTMLObjects */
class kGUIHTMLColor
{
public:
	kGUIHTMLColor() {m_transparent=false;m_color=DrawColor(0,0,0);};
	void Set(kGUIHTMLColor *c) {m_transparent=c->m_transparent;m_color=c->m_color;}
	void Set(kGUIColor c) {m_transparent=false;m_color=c;}
	void SetTransparent(bool t) {m_transparent=t;}
	bool GetTransparent(void) {return m_transparent;}
	kGUIColor GetColor(void) {return m_color;}
	void CopyFrom(kGUIHTMLColor *c) {m_transparent=c->m_transparent;m_color=c->m_color;}
private:
	bool m_transparent;
	kGUIColor m_color;
};

#define BORDER_LEFT 1
#define BORDER_RIGHT 2
#define BORDER_TOP 4
#define BORDER_BOTTOM 8
#define BORDER_ALL (BORDER_LEFT|BORDER_RIGHT|BORDER_TOP|BORDER_BOTTOM)

#define MARGIN_LEFT 1
#define MARGIN_RIGHT 2
#define MARGIN_TOP 4
#define MARGIN_BOTTOM 8
#define MARGIN_ALL (MARGIN_LEFT|MARGIN_RIGHT|MARGIN_TOP|MARGIN_BOTTOM)

#define PADDING_LEFT 1
#define PADDING_RIGHT 2
#define PADDING_TOP 4
#define PADDING_BOTTOM 8
#define PADDING_ALL (PADDING_LEFT|PADDING_RIGHT|PADDING_TOP|PADDING_BOTTOM)

/*! HTML box, contains border, margins, pad
    @ingroup kGUIHTMLObjects */
class kGUIHTMLBox
{
public:
	kGUIHTMLBox(kGUIHTMLPageObj *page);
	void Reset(void);
	bool GetValid(void);		/* false=same state as reset, true=has valid settings */
	void SetBorder(unsigned int w);
	void SetBorderWidth(unsigned int bb,kGUIString *s,class kGUIHTMLObj *parent);
	void SetBorderColor(unsigned int bb,kGUIString *s);
	void SetBorderStyle(unsigned int bb,kGUIString *s);

	void GetMargins(kGUICorners *in,kGUICorners *out);
	void SetMarginWidth(unsigned int mm,kGUIString *s,kGUIHTMLObj *parent);
	int GetMarginAlign(void);
	void SetPaddingWidth(unsigned int pp,kGUIString *s,kGUIHTMLObj *parent);

	unsigned int GetBoxLeftMargin(void) {return m_leftmw;}
	unsigned int GetBoxRightMargin(void) {return m_rightmw;}
	void SetBoxLeftMargin(unsigned int lm) {m_leftmw=lm;}
	void SetBoxRightMargin(unsigned int rm) {m_rightmw=rm;}

	unsigned int GetBoxWidth(void) {return m_bw;}
	unsigned int GetBoxTopWidth(void);
	unsigned int GetBoxLeftWidth(void);
	unsigned int GetBoxRightWidth(void);
	unsigned int GetBoxBottomWidth(void);

	void Draw(kGUICorners *c);	/* shrinks corners after drawing */
private:
	kGUIHTMLPageObj *m_page;
	unsigned int m_bw;
	unsigned int m_topbw;
	unsigned int m_leftbw;
	unsigned int m_rightbw;
	unsigned int m_bottombw;
	unsigned int m_topmw;
	unsigned int m_leftmw;
	unsigned int m_rightmw;
	unsigned int m_bottommw;
	unsigned int m_marginauto:4;
	unsigned int m_toppw;
	unsigned int m_leftpw;
	unsigned int m_rightpw;
	unsigned int m_bottompw;
	kGUIHTMLColor m_topcolor;
	kGUIHTMLColor m_leftcolor;
	kGUIHTMLColor m_rightcolor;
	kGUIHTMLColor m_bottomcolor;
	unsigned int m_topstyle;
	unsigned int m_leftstyle;
	unsigned int m_rightstyle;
	unsigned int m_bottomstyle;
	void DrawLine(unsigned int side,int index,int num,int x1,int y1,int x2,int y2,kGUIColor c,int style);
	kGUIColor Dark(kGUIColor c);
	kGUIColor Light(kGUIColor c);
};

/*! HTML margin
    @ingroup kGUIHTMLObjects */
class kGUIHTMLMargin
{
public:
	kGUIHTMLMargin(kGUIHTMLPageObj *page);
	void Reset(void);
private:
	unsigned int m_leftmargin;
	unsigned int m_rightmargin;
	unsigned int m_bottommargin;
	unsigned int m_topmargin;
};

/* priority is so that if there are multiple linked stylesheets then each */
/* is assigned a different priority based on the order encountered in the page */
/* that way if they load in a different order, they are still built correctly */
/* because of the priority */

/*! HTML attributes attached to tags or rules
    @ingroup kGUIHTMLObjects */
class kGUIHTMLAttrib
{
public:
	kGUIHTMLAttrib() {m_owner=0;m_id=0;m_vid=0;m_priority=0;}

	void SetOwner(unsigned int owner) {m_owner=owner;}
	void SetPriority(unsigned int priority) {m_priority=priority;}
	void SetID(unsigned int id) {m_id=id;}
	void SetValue(kGUIString *value);

	unsigned int GetID(void) {return m_id;}
	unsigned int GetOwner(void) {return m_owner;}
	unsigned int GetPriority(void) {return m_priority;}
	int GetVID(void) {return m_vid;}
	kGUIString *GetValue(void) {return &m_value;} 
private:
	unsigned int m_owner:3;
	unsigned int m_id:13;
	int m_vid:16;
	unsigned int m_priority;
	kGUIString m_value;
};

/*! HTML table class used to contain and position cells
    @ingroup kGUIHTMLObjects */
class kGUIHTMLTableInfo
{
public:
	kGUIHTMLTableInfo();
	~kGUIHTMLTableInfo();
	void CalcMinMax(kGUIHTMLObj *table,int em);
	void PositionCells(kGUIHTMLObj *table);
	void ExpandCols(int startcol,int numcols,int width,bool expand,bool applypercents);
	void ExpandTable(kGUIHTMLObj *table,int em);
	int GetSpanWidth(int startcol,int endcol);
	int GetSpanHeight(int startrow,int endrow);
	void Get(kGUIHTMLObj *obj,Array<kGUIHTMLObj *>*objectarray,unsigned int *num,unsigned int tagid);
	unsigned int m_numrows;
	unsigned int m_numcols;

	kGUIHTMLBox *m_box;			/* copy of tables border info */
	kGUIHTMLBox *m_cellborder;		/* all cells share this */
	int m_cellspacing;
	int m_cellpadding;
	Array<int>m_colx;
	Array<int>m_coly;
	Array<int>m_colwidth;
	Array<bool>m_colwidthfixed;
	Array<int>m_colmin;
	Array<int>m_colmax;
	Array<int>m_colwidthpercent;
	Array<int>m_rowheight;
	Array<kGUIHTMLObj *>m_rowptrs;
	Array<kGUIHTMLObj *>m_cellptrs;
};

/* online image is one that can also be passed a URL for an image */

enum
{
ALIGN_UNDEFINED,
ALIGN_LEFT,
ALIGN_RIGHT,
ALIGN_CENTER,
ALIGN_ABSCENTER,
ALIGN_JUSTIFY};		/* needs 3 bits */

enum
{
VALIGN_TOP,
VALIGN_MIDDLE,
VALIGN_BOTTOM,
VALIGN_ABSTOP,
VALIGN_ABSMIDDLE,
VALIGN_ABSBOTTOM,
VALIGN_BASELINE,
VALIGN_SUB,
VALIGN_SUPER,
VALIGN_OFFSET};	/* needs 4 bits */

enum
{
LINKTYPE_CSS,
LINKTYPE_HTML,
LINKTYPE_ICON,
LINKTYPE_UNKNOWN
};

/*! HTML link class, this is not a clickable link but a link to external content like css pages
    @ingroup kGUIHTMLObjects */
class kGUIOnlineLink : public DataHandle
{
public:
	kGUIOnlineLink(kGUIHTMLPageObj *page) {m_page=page;m_flush=false;m_loadpending=false;}
	void SetURL(kGUIString *url,kGUIString *referrer,unsigned int type);
	bool CacheURL(kGUIString *url,unsigned int type,kGUIString *fn);
	kGUIString *GetURL(void) {return &m_url;}
	kGUIString *GetReferrer(void) {return &m_referrer;}
	void SetMedia(kGUIString *m) {m_media.SetString(m);}
	kGUIString *GetMedia(void) {return &m_media;}
	unsigned int GetType(void) {return m_type;}
	kGUIDownloadEntry *GetDL(void) {return &m_dl;}

	void SetPriority(int priority) {m_priority=priority;}
	unsigned int GetPriority(void) {return m_priority;}

	void SetHeader(kGUIString *header) {m_header.SetString(header);}
	kGUIString *GetHeader(void) {return &m_header;}

	bool GetLoadPending(void) {return m_loadpending;}
	void SetLoadPending(bool l) {m_loadpending=l;}
	void Flush(void) {m_flush=true;}
	void Abort(void) {m_dl.Abort();}
	void SetLoadedCallback(void *codeobj,void (*code)(void *,kGUIOnlineLink *)) {m_loadedcallback.Set(codeobj,code);}
	CALLBACKGLUEVAL(kGUIOnlineLink,LoadFinished,int);
private:
	void LoadFinished(int status);
	bool m_flush:1;
	bool m_loadpending:1;
	unsigned int m_priority;
	kGUIHTMLPageObj *m_page;
	kGUIString m_url;
	kGUIString m_referrer;
	kGUIString m_header;
	kGUIString m_media;
	unsigned int m_type;
	DataHandle m_dh;	/* contents of loaded data */
	kGUIDownloadEntry m_dl;
	kGUICallBackPtr<kGUIOnlineLink>m_loadedcallback;
};

/*! HTML image class
    @ingroup kGUIHTMLObjects */
class kGUIOnlineImage : public kGUIImage
{
public:
	kGUIOnlineImage() {m_loadtriggered=false;m_loadaborted=false;}
	kGUIString *GetURL(void) {return &m_url;}
	void SetPage(kGUIHTMLPageObj *page) {m_page=page;}
	void SetURL(kGUIString *url,kGUIString *referrer);
	void Purge(void);
	void Abort(void) {m_dl.Abort();}
	bool GetLoadTriggered(void) {return m_loadtriggered;}
	void SetLoadTriggered(bool lt) {m_loadtriggered=lt;}
	bool GetLoadAborted(void) {return m_loadaborted;}
	void SetLoadAborted(bool la) {m_loadaborted=la;}
private:
	CALLBACKGLUEVAL(kGUIOnlineImage,LoadFinished,int);
	void LoadFinished(int status);
	bool m_loadtriggered:1;
	bool m_loadaborted:1;
	kGUIHTMLPageObj *m_page;
	kGUIString m_url;
	kGUIDownloadEntry m_dl;
};

/* todo: handle displaying "alt" if image cannot be loaded */

/*! HTML image object class
    @ingroup kGUIHTMLObjects */
class kGUIOnlineImageObj : public kGUIImageRefObj
{
public:
	kGUIOnlineImageObj() {m_link=0;m_map=0;m_valid=false;}
	bool UpdateInput(void);
	void Draw(void);
	void SetPage(kGUIHTMLPageObj *page) {m_page=page;}
	void SetMap(class kGUIHTMLMap *map) {m_map=map;}
	kGUIString *GetURL(void) {return &m_url;}
	void SetIsValid(bool v) {m_valid=v;}
	bool GetIsValid(void) {return m_valid;}
	void SetURL(kGUIHTMLPageObj *page,kGUIString *url,kGUIString *referrer);
	int GetImageHeight(void) {return GetImage()?GetImage()->GetImageHeight():0;}
	int GetImageWidth(void) {return GetImage()?GetImage()->GetImageWidth():0;}
	void SetLink(kGUIHTMLLinkObj *link) {m_link=link;}
	kGUIHTMLLinkObj *GetLink(void) {return m_link;}
	DataHandle *GetDataHandle(void) {return GetImage();}
private:
	bool m_valid:1;
	kGUIString m_url;
	kGUIHTMLPageObj *m_page;
	kGUIHTMLLinkObj *m_link;
	class kGUIHTMLMap *m_map;
};

/*! HTML button with an image object class for use in forms
    @ingroup kGUIHTMLObjects */
class kGUIHTMLButtonImageObj : public kGUIOnlineImageObj
{
public:
	kGUIHTMLButtonImageObj() {}
	kGUIHTMLButtonImageObj(kGUIHTMLObj *styleparent) {m_styleparent=styleparent;}
	bool UpdateInput(void);
private:
	kGUIHTMLObj *m_styleparent;
};

/*! HTML style class, used to hold attributes, used for tags and rules
    @ingroup kGUIHTMLObjects */
class kGUIStyleObj
{
public:
	kGUIStyleObj() {m_ownerurl=0;m_numattribs=0;m_attributes.Init(16,16);}
	virtual ~kGUIStyleObj() {PurgeStyles();}
	void PurgeStyles(void) {unsigned int i;for(i=0;i<m_numattribs;++i) delete m_attributes.GetEntry(i);m_numattribs=0;}
	unsigned int GetNumAttributes(void) {return m_numattribs;}
	kGUIHTMLAttrib *GetAttrib(int n) {return m_attributes.GetEntry(n);}
	kGUIHTMLAttrib *FindAttrib(unsigned int id);

	void SetOwnerURL(unsigned int ownerid) {m_ownerurl=ownerid;}
	unsigned int GetOwnerURL(void) {return m_ownerurl;}

	void AddAttributes(kGUIHTMLPageObj *page,unsigned int content,unsigned int baseowner,unsigned int priority,kGUIString *s);

	/* this splits attributes that take multiple values into their individual values */
	void AddAndSplitAttribute(kGUIHTMLPageObj *page,unsigned int content,unsigned int baseowner,unsigned int priority,unsigned int attid,kGUIString *value,bool addempty);

	/* this call checks for duplicates and updates the value if the att already exists */
	/* also nulls values are ignored */
	void AddAttribute(unsigned int owner,unsigned int priority,unsigned int attid,kGUIString *value);

	/* this call allows null values */
	void AddAttributez(unsigned int owner,unsigned int priority,unsigned int attid,kGUIString *value);

	/* this call adds attributes regardless so the list can have duplicate attribute ids */
	void AppendAttribute(unsigned int id,kGUIString *value) {kGUIHTMLAttrib *att;att=new kGUIHTMLAttrib();att->SetOwner(OWNER_AUTHOR);att->SetID(id);att->SetValue(value);m_attributes.SetEntry(m_numattribs++,att);};
private:
	unsigned int m_ownerurl;	/* index using stringtoidcase */
	unsigned int m_numattribs;
	Array<kGUIHTMLAttrib *>m_attributes;
};

typedef struct
{
	unsigned int m_selector:16;
	bool m_not:1;
	unsigned int m_value;
	unsigned int m_compare;
}kGUIHTMLSelector;

/*! HTML rule class, holds selectors and attributes
    @ingroup kGUIHTMLObjects */
class kGUIHTMLRule : public kGUIStyleObj
{
public:
	kGUIHTMLRule(kGUIHTMLPageObj *page);
	~kGUIHTMLRule() {}
	bool Parse(kGUIString *string);
	bool ReadString(kGUIReadString *rs,kGUIString *s);
	unsigned int GetPseudoClass(unsigned int tokenid);
	void GetString(kGUIString *string);
	void CalcScore(void);
	int Compare(kGUIHTMLRule *r2);
	int GetNumSelectors(void) {return m_numentries;}
	bool GetLast(void) {return m_last;}
	bool Evaluate(kGUIHTMLObj *ho,unsigned int lasttime) {if(lasttime==m_lasttime) return m_last;m_lasttime=lasttime;m_hitcomplex=false;m_last=Evaluate(m_numentries-1,ho);return m_last;}
	bool GetSimple(void) {return m_simple;}
	bool GetHitComplex(void) {return m_hitcomplex;}
	bool GetUsesBefore(void) {return m_before;}
	bool GetUsesAfter(void) {return m_after;}

	void SetPossible(bool p) {m_possible=p;}
	bool GetPossible(void) {return m_possible;}
	void AddRefQuick(void) {++m_numcurrefs;}
	void AddRef(void) {if(++m_numcurrefs==m_numrefs)m_possible=true;}
	void SubRef(void) {--m_numcurrefs;m_possible=false;}

	void SetLastTime(int t) {m_lasttime=t;}

	void SetNumRefs(int n) {m_numrefs=n;}
	void SetCurNumRefs(int n) {m_numcurrefs=n;}
	int GetNumRefs(void) {return m_numrefs;}
	int GetCurNumRefs(void) {return m_numcurrefs;}

	void UpdateNumOwnerStyles(void);
	unsigned int GetNumOwnerStyles(unsigned int owner) {return m_numownerstyles[owner];}
	void ResetLastTime(void) {m_lasttime=0;}
private:
	bool Evaluate(int sindex,kGUIHTMLObj *ho);
	kGUIHTMLPageObj *m_page;
	unsigned int m_lasttime;
	bool m_simple:1;
	bool m_hitcomplex:1;
	bool m_last:1;
	bool m_before:1;
	bool m_after:1;
	bool m_possible:1;

	/* these are used so only rules for each valid owner level are in the sorted rule list */
	unsigned int m_numownerstyles[OWNER_NUM];

	/* these are used for the 'score' function */
	int m_numids;
	int m_numclasses;
	int m_numtags;

	/* the sum of these should match m_numentries */
	unsigned int m_numentries;
	Array<kGUIHTMLSelector>m_entries;
	Array<unsigned int>m_sorder;

	/* optimize speed data */
	int m_numrefs;
	int m_numcurrefs;
};

enum		//needs 5 bits
{
DISPLAY_NONE,
DISPLAY_BLOCK,
DISPLAY_INLINE,
DISPLAY_INLINE_BLOCK,
DISPLAY_TABLE,
DISPLAY_INLINE_TABLE,
DISPLAY_TABLE_ROW_GROUP,
DISPLAY_TABLE_ROW,
DISPLAY_TABLE_HEADER_GROUP,
DISPLAY_TABLE_FOOTER_GROUP,
DISPLAY_TABLE_COLUMN_GROUP,
DISPLAY_TABLE_COLUMN,
DISPLAY_TABLE_CELL,
DISPLAY_TABLE_CAPTION,
DISPLAY_LIST_ITEM,
DISPLAY_COMPACT,
DISPLAY_RUN_IN,
DISPLAY_MARKER,
DISPLAY_ANONYMOUS
};

enum
{
VISIBLE_HIDDEN,
VISIBLE_COLLAPSE,
VISIBLE_VISIBLE};

enum
{
OVERFLOW_VISIBLE,
OVERFLOW_HIDDEN,
OVERFLOW_SCROLL,
OVERFLOW_AUTO
};

/* text is displayed left to right (like english) or right to left ( like japanese ) */
enum
{
	TEXTDIR_LTR,
	TEXTDIR_RTL
};

enum 
{
CID_ID,
CID_CLASS
};

typedef struct
{
	unsigned int m_type:2;
	unsigned int m_id:30;
}CID_DEF;

typedef struct
{
	int above;
	int baseline;
	int below;
	kGUIObj *obj;
	int width;		/* width when added, used for debugging */
	int height;		/* height when added, used for debugging */
}PO_DEF;

/*! HTML position info class, these are used during the position pass to layout
    the page. One is used for each nested child level.
    @ingroup kGUIHTMLObjects */
class kGUIHTMLPosInfo
{
public:
	kGUIHTMLPosInfo () {m_ponum=0;m_polist.Init(256,32);}
	int m_ponum;		/* number of position objects */
	int m_curx;
	int m_cury;

	int m_leftw;	/* object on left ( image or table ) */
	int m_rightw;	/* object on right ( image or table ) */
	int m_lefth;	/* remaining height for image on left */
	int m_righth;	/* remaining height for image on right */

	int m_lineasc;
	int m_linedesc;

	Array<PO_DEF>m_polist;

};

/*! @internal @class kGUIHTMLObj
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML object class, this is the object generated for each html tag
    @ingroup kGUIHTMLObjects */
class kGUIHTMLObj : public kGUIStyleObj, public kGUIContainerObj
{
	friend class kGUIHTMLLIPrefix;
	friend class kGUIHTMLTextGroup;
	friend class kGUIHTMLContentGroup;
	friend class kGUIHTMLPageObj;
	friend class kGUIHTMLTableInfo;
	friend class kGUIHTMLButtonTextObj;
	friend class kGUIHTMLButtonImageObj;
	friend class kGUIHTMLFormObj;
	friend class kGUIHTMLRule;
public:
	kGUIHTMLObj();
	kGUIHTMLObj(class kGUIHTMLObj *renderparent,class kGUIHTMLPageObj *page,TAGLIST_DEF *tag);
	~kGUIHTMLObj();
	void Init(void);
	void Purge(void);
	kGUIHTMLPageObj *GetPage(void) {return m_page;}
	void SetID(int id);
	unsigned int GetID(void) {return m_id;}
	void SetSubID(int subid) {m_subid=subid;}
	unsigned int GetSubID(void) {return m_subid;}
	void ChangeDisplay(unsigned int olddisplay);
	void DrawBG(kGUICorners *c);
	void SetParent(kGUIHTMLObj *parent) {m_styleparent=parent;}
	void SetPage(kGUIHTMLPageObj *page) {m_page=page;}
	void Position(bool placeme=true);
	void Contain(void);
	void InsertFrame(void);
	bool DetectObject(void);
    bool UpdateHover(void);
	void ClipMinMaxWidth(int pw);
	void ClipMinMaxHeight(int ph);
	void CheckFixed(void);

	void SetAttributes(kGUIStyleObj *slist,unsigned int owner);
	unsigned int GetNumStyleChildren(void) {return m_numstylechildren;}
	void AddStyleChild(kGUIHTMLObj *child) {child->SetParent(this);m_stylechildren.SetEntry(m_numstylechildren++,child);}

	/* these two are used by the LI tag */
	void InsertStyleChild(int index,kGUIHTMLObj *child) {child->SetParent(this);m_stylechildren.InsertEntry(m_numstylechildren,index,1);m_stylechildren.SetEntry(index,child);m_numstylechildren++;}
	void DelStyleChild(kGUIHTMLObj *child) {m_stylechildren.Delete(child);--m_numstylechildren;}

	kGUIHTMLObj *FindStyleChild(unsigned int type);
	void AddRenderObject(kGUIObj *obj);
	void SetDisplay(unsigned int d) {m_display=d;}
	void SetAlign(unsigned int a) {m_align=a;}
	unsigned int GetTextAlign(void) {return m_textalign;}
	void SetTextAlign(unsigned int a) {m_textalign=a;}
	unsigned int GetAlign(void);
	void SetVAlign(unsigned int a) {m_valign=a;}
	unsigned int GetVAlign(void) {return m_valign;}
	kGUIHTMLBox *GetBox(void);
	void GenerateSource(kGUIString *cs,unsigned int depth);
	static kGUIHTMLFormObj *GetForm(kGUIHTMLObj *o);
	bool GetHover(void) {return m_hover;}
	void SetActive(bool a) {m_active=a;}

	void SetString(kGUIString *string,bool plusspace,bool pluscr);

	void Draw(void);
	void CalcChildZone(void);
	void CalcChildZone(int yoff);
	bool UpdateInput(void) {return UpdateInputC(0);}
	kGUIHTMLObj *GetParentObj(void);

	void SavePosition(void);
	void ComparePosition(void);

	unsigned int GetEM(void) {return m_em;}

	void SetOutsideW(int w) {MoveZoneW(w);}
	void SetOutsideH(int h) {MoveZoneH(h);}
	int GetOutsideW(void) {return(GetZoneW());}
	int GetOutsideH(void) {return (GetZoneH());}

	void SetInsideW(int w) {if(m_box){w+=m_box->GetBoxLeftWidth()+m_box->GetBoxRightWidth();}MoveZoneW(w);}
	void SetInsideH(int h) {if(m_box){h+=m_box->GetBoxTopWidth()+m_box->GetBoxBottomWidth();}MoveZoneH(h);}
	int GetInsideW(void) {int w;w=GetZoneW();if(m_box){w-=m_box->GetBoxLeftWidth()+m_box->GetBoxRightWidth();}return(w);}
	int GetInsideH(void) {int h;h=GetZoneH();if(m_box){h-=m_box->GetBoxTopWidth()+m_box->GetBoxBottomWidth();}return(h);}

	void SetPosInfo(kGUIHTMLPosInfo *pos) {m_pos=pos;}
private:
	CALLBACKGLUEPTR(kGUIHTMLObj,RadioChanged,kGUIEvent)
	void RadioChanged(kGUIEvent *event);

	void Clear(int c);
	void PositionHardBreak(int lineheight);
	void PositionBreak(bool wrap=false);
	void PositionChild(kGUIHTMLObj *obj,kGUIObj *robj,int asc,int desc);

	TAGLIST_DEF *m_tag;
	class kGUIHTMLRuleCache *m_rulecache;
	unsigned int m_id;
	unsigned int m_numcids;
	Array<CID_DEF> m_cids;

	kGUIHTMLBox *m_box;
	kGUIHTMLPageObj *m_page;
	kGUIHTMLObj *m_renderparent;
	kGUIHTMLObj *m_styleparent;
	kGUIString *m_string;
	kGUIHTMLObj *m_beforeobj;
	kGUIHTMLObj *m_afterobj;

	unsigned int m_subid:8;
	bool m_error:1;
	bool m_fixedw:1;
	bool m_fixedh:1;
	bool m_relw:1;
	bool m_relh:1;
	bool m_fixedpos:1;
	bool m_relpos:1;
	bool m_skipbr:1;
	unsigned int m_em:12;
	unsigned int m_lh:12;
	unsigned int m_display:5;
	unsigned int m_visible:2;
	unsigned int m_overflowx:2;
	unsigned int m_overflowy:2;
	union
	{
		kGUIHTMLTextGroup *m_textgroup;
		kGUIHTMLContentGroup *m_contentgroup;
		kGUIHTMLLIPrefix *m_liprefix;
		kGUIHTMLShapeObj *m_shapeobj;
		kGUIHTMLTextObj *m_textobj;
		kGUIText *m_text;
		kGUIOnlineImageObj *m_imageobj;
		kGUIRectObj *m_rectobj;
		kGUIOnlineLink *m_linked;	/* this is a link to an external object, not a clickable link */
		kGUIHTMLLinkObj *m_linkobj;
		kGUIHTMLFormObj *m_formobj;
		kGUIHTMLInputBoxObj *m_inputobj;
		kGUIHTMLButtonTextObj *m_buttontextobj;
		kGUIHTMLButtonImageObj *m_buttonimageobj;
		kGUITickBoxObj *m_tickobj;
		kGUIComboBoxObj *m_comboboxobj;
		kGUIRadioObj *m_radioobj;
		kGUIListboxObj *m_listboxobj;
		kGUIObj *m_singleobj;
	}m_obj;
	kGUIUnits m_width;
	kGUIUnits m_height;
	kGUIUnits m_left;
	kGUIUnits m_right;
	kGUIUnits m_top;
	kGUIUnits m_bottom;
	kGUIUnits m_minwidth;
	kGUIUnits m_minheight;
	kGUIUnits m_maxwidth;
	kGUIUnits m_maxheight;
	kGUIUnits m_valignoffset;

	bool m_insert:1;
	bool m_hover:1;
	bool m_active:1;
	bool m_washover:1;
	bool m_useshover:1;
	unsigned int m_position:3;
	unsigned int m_float:2;
	unsigned int m_clear:2;
	unsigned int m_textalign:3;
	unsigned int m_align:3;
	unsigned int m_potextalign:3;
	unsigned int m_valign:4;
	unsigned int m_dir:1;
	bool m_bgrepeatx:1;
	bool m_bgrepeaty:1;
	bool m_bgfixed:1;
	bool m_objinit:1;
	bool m_hashover:1;		/* there is a hover style for this tag, so refresh when hover status changes */

	kGUIUnits m_bgx,m_bgy;
	kGUIOnlineImageObj m_bgimage;
	kGUIHTMLColor m_bgcolor;

	int m_minw;
	int m_maxw;
	int m_maxy;
	int m_maxchildy;
	bool m_childusesheight;	/* one of my children usus my height */

	int m_colspan,m_rowspan;	/* used for TD and TH only */

	int m_saveminw;
	int m_savemaxw;
	int m_savew;
	int m_saveh;

	/*! this is a pointer to the position class, only valid when this object is */
	/* currently in the position heiarchy */
	kGUIHTMLPosInfo *m_pos;

	kGUIHTMLTableInfo *m_ti;
	kGUIColor m_bordercolor1;
	kGUIColor m_bordercolor2;

	unsigned int m_numstylechildren;
	Array<kGUIHTMLObj *>m_stylechildren;
};

/*! @internal @struct ATTLIST_DEF
	@brief Internal struct used by the kGUIHTMLPageObj class.
	List of Attribute names and their associated IDs */
typedef struct
{
	const char *name;
	unsigned int attid;
}ATTLIST_DEF;

/*! @internal @struct CONSTLIST_DEF
	@brief Internal struct used by the kGUIHTMLPageObj class.
	List of Constant names and their associated IDs */
typedef struct
{
	const char *name;
	int id;
}CONSTLIST_DEF;

/*! @internal @struct STYLERESTORE_DEF
	@brief Internal sruct used by the kGUIHTMLPageObj class.
	Structure for popping css styles off of the save/restore stack */
typedef struct
{
	void *place;
	int numbytes;
}STYLERESTORE_DEF;

/*! @internal @struct POPLIST_DEF
	@brief Internal struct used by the kGUIHTMLPageObj class.
	Structure for child tags that are not allowed inside the associated parent tag */
typedef struct
{
unsigned int parenttagid;
unsigned int childtagid;
}POPLIST_DEF;

enum
{
HTMLATT_ALINK,
HTMLATT_BACKGROUND,
HTMLATT_BACKGROUND_IMAGE,
HTMLATT_BACKGROUND_ATTACHMENT,
HTMLATT_BACKGROUND_REPEAT,
HTMLATT_BACKGROUND_POSITIONX,
HTMLATT_BACKGROUND_POSITIONY,
HTMLATT_BACKGROUND_COLOR,
HTMLATT_BORDER_COLOR_TOP,
HTMLATT_BORDER_COLOR_BOTTOM,
HTMLATT_BORDER_COLOR_LEFT,
HTMLATT_BORDER_COLOR_RIGHT,
HTMLATT_BORDER_SPACING_HORIZ,
HTMLATT_BORDER_SPACING_VERT,
HTMLATT_BORDER_STYLE_TOP,
HTMLATT_BORDER_STYLE_BOTTOM,
HTMLATT_BORDER_STYLE_LEFT,
HTMLATT_BORDER_STYLE_RIGHT,
HTMLATT_BORDER_WIDTH,
HTMLATT_BORDER_WIDTH_TOP,
HTMLATT_BORDER_WIDTH_BOTTOM,
HTMLATT_BORDER_WIDTH_LEFT,
HTMLATT_BORDER_WIDTH_RIGHT,
HTMLATT_BORDER_COLLAPSE,
HTMLATT_BORDERCOLOR,
HTMLATT_BOTTOM,
HTMLATT_CELLPADDING,
HTMLATT_CELLSPACING,
HTMLATT_CLEAR,
HTMLATT_COLOR,
HTMLATT_COLS,
HTMLATT_COLSPAN,
HTMLATT_COUNTER_RESET,
HTMLATT_COUNTER_INCREMENT,
HTMLATT_CURSOR,
HTMLATT_DIRECTION,
HTMLATT_DISABLED,
HTMLATT_DISPLAY,
HTMLATT_FLOAT,
HTMLATT_FONT_FAMILY,
HTMLATT_FONT_STYLE,
HTMLATT_FONT_VARIANT,
HTMLATT_FONT_WEIGHT,
HTMLATT_FONT_SIZE,
HTMLATT_FONT_SIZE_ADJUST,
HTMLATT_HEIGHT,
HTMLATT_HREF,
HTMLATT_LEFT,
HTMLATT_LINK,
HTMLATT_LINE_HEIGHT,
HTMLATT_LIST_STYLE_IMAGE,
HTMLATT_LIST_STYLE_POSITION,
HTMLATT_LIST_STYLE_TYPE,
HTMLATT_MARGIN,
HTMLATT_MARGIN_BOTTOM,
HTMLATT_MARGIN_LEFT,
HTMLATT_MARGIN_RIGHT,
HTMLATT_MARGIN_TOP,
HTMLATT_MARGIN_HEIGHT,
HTMLATT_MARGIN_WIDTH,
HTMLATT_MAXLENGTH,
HTMLATT_MINHEIGHT,
HTMLATT_MAXHEIGHT,
HTMLATT_MINWIDTH,
HTMLATT_MAXWIDTH,
HTMLATT_NOWRAP,
HTMLATT_OUTLINE,
HTMLATT_OVERFLOW_X,
HTMLATT_OVERFLOW_Y,
HTMLATT_PADDING_LEFT,
HTMLATT_PADDING_RIGHT,
HTMLATT_PADDING_TOP,
HTMLATT_PADDING_BOTTOM,
HTMLATT_PAGE_BREAK_AFTER,
HTMLATT_PAGE_BREAK_INSIDE,
HTMLATT_POSITION,
HTMLATT_RIGHT,
HTMLATT_ROWS,
HTMLATT_ROWSPAN,
HTMLATT_STYLE,
HTMLATT_TEXT_ALIGN,
HTMLATT_TEXT_INDENT,
HTMLATT_TEXT_DECORATION,
HTMLATT_TEXT_SHADOW_X,
HTMLATT_TEXT_SHADOW_Y,
HTMLATT_TEXT_SHADOW_R,
HTMLATT_TEXT_SHADOW_COLOR,
HTMLATT_TEXT_TRANSFORM,
HTMLATT_LETTER_SPACING,
HTMLATT_WORD_SPACING,
HTMLATT_TOP,
HTMLATT_VALIGN,
HTMLATT_VERTICAL_ALIGN,
HTMLATT_VISIBILITY,
HTMLATT_VLINK,
HTMLATT_WHITE_SPACE,
HTMLATT_WIDTH,
HTMLATT_WRAP,
HTMLATT_Z_INDEX,
HTMLATT_LANG,
HTMLATT_TABLE_LAYOUT,
HTMLATT_ZOOM,
HTMLATT_CONTENT_BEFORE,
HTMLATT_CONTENT_AFTER,

HTMLATT_UNKNOWN,

/* these can contain multiple parameters and are broken down into their individual attributes when pre-processed */
HTMLATTGROUP_BACKGROUND_POSITION,
HTMLATTGROUP_PADDING,
HTMLATTGROUP_BORDER,
HTMLATTGROUP_BORDER_STYLE,
HTMLATTGROUP_BORDER_COLOR,
HTMLATTGROUP_BORDER_WIDTH,
HTMLATTGROUP_BORDER_TOP,
HTMLATTGROUP_BORDER_BOTTOM,
HTMLATTGROUP_BORDER_LEFT,
HTMLATTGROUP_BORDER_RIGHT,
HTMLATTGROUP_BORDER_SPACING,
HTMLATTGROUP_TEXT_SHADOW,
HTMLATTGROUP_LIST_STYLE,
HTMLATT_OVERFLOW,				/* converts to OVERFLOW_X and OVERFLOW_Y */
HTMLATT_HSPACE,					/* converts to MARGIN_LEFT and MARGIN_RIGHT  */
HTMLATT_VSPACE,					/* converts to MARGIN_TOP and MARGIN_BOTTOM */
HTMLATT_HREFLANG,
HTMLATT_CITE,
HTMLATT_VOICE_FAMILY,
HTMLATT_UNKNOWN2,

/* this needs to be broken down */
HTMLATTGROUP_FONT,

/* these are looked up by specific tags and not handled in the regular setattributes code */
HTMLATT_CLASS,
HTMLATT_ID,
HTMLATT_SIZE,
HTMLATT_SRC,
HTMLATT_CHECKED,
HTMLATT_CHARSET,
HTMLATT_SELECTED,
HTMLATT_SCROLLING,
HTMLATT_LONGDESC,
HTMLATT_SCOPE,
HTMLATT_ACTION,
HTMLATT_FACE,
HTMLATT_FOR,
HTMLATT_VALUE,
HTMLATT_FRAMEBORDER,
HTMLATT_TITLE,
HTMLATT_START,
HTMLATT_LABEL,
HTMLATT_METHOD,
HTMLATT_TARGET,
HTMLATT_SUMMARY,
HTMLATT_CONTENT,
HTMLATT_COMMENT,
HTMLATT_XMLNS,
HTMLATT_XMLNS_V,
HTMLATT_MEDIA,
HTMLATT_REL,
HTMLATT_ONBLUR,
HTMLATT_ONCHANGE,
HTMLATT_ONKEYPRESS,
HTMLATT_ONFOCUS,
HTMLATT_ONSUBMIT,
HTMLATT_ONCLICK,
HTMLATT_ONERROR,
HTMLATT_ONLOAD,
HTMLATT_ONMOUSEDOWN,
HTMLATT_ONMOUSEOVER,
HTMLATT_ONMOUSEOUT,
HTMLATT_LANGUAGE,
HTMLATT_ALT,
HTMLATT_HTTP_EQUIV,
HTMLATT_TYPE,
HTMLATT_NAME,
HTMLATT_DATA,
HTMLATT_OPACITY,
HTMLATT_RULES,
HTMLATT_ACCESSKEY,
HTMLATT_TABINDEX,
HTMLATT_DEFER,
HTMLATT_PROFILE,

HTMLATT_SHAPE,
HTMLATT_COORDS,
HTMLATT_USEMAP,
HTMLATT_NOHREF,
HTMLATT_MULTIPLE,

HTMLATT_ERROR,	/* internal code used for content before/after/not allowed*/

HTMLATT_NUM};

/*! @internal @class AsyncLoadInfo
	@brief Internal class used by the kGUIHTMLPageObj class.
    Async info for what to do when async file has finished loading */
class AsyncLoadInfo
{
public:
	DataHandle *m_dh;
	kGUIDownloadEntry *m_dl;
	kGUICallBackInt m_donecallback;
};


/*! @internal @class kGUIHTMLRuleList 
	@brief Internal class used by the kGUIHTMLPageObj class.
	HTML rule list class, holds an array of rule list object pointers
    @ingroup kGUIHTMLObjects */
class kGUIHTMLRuleList
{
public:
	kGUIHTMLRuleList() {m_num=0;m_rules.Init(512,64);}
	void Add(kGUIHTMLRule *rule) {m_rules.SetEntry(m_num++,rule);}
	unsigned int m_num;
	Array<kGUIHTMLRule *> m_rules;
};

/*! HTML area class, used for clickable areas on images
    @ingroup kGUIHTMLObjects */
class kGUIHTMLArea
{
public:
	kGUIHTMLArea() {m_haslink=false;m_type=0;m_numpoints=0;m_points.Init(4,4);}
	void Init(unsigned int type) {m_type=type;m_numpoints=0;}
	void AllocPoints(unsigned int num) {m_points.Alloc(num);}
	void SetTag(kGUIHTMLObj *tag);
	unsigned int GetType(void) {return m_type;}
	unsigned int GetNumPoints(void) {return m_numpoints;}
	kGUIHTMLLinkObj *GetLink(void) {return m_haslink?&m_linkobj:0;}

	kGUIPoint2 *GetArrayPtr(void) {return m_points.GetArrayPtr();}
	int GetPointX(int n) {return m_points.GetEntryPtr(n)->x;}
	int GetPointY(int n) {return m_points.GetEntryPtr(n)->y;}
	void AddPoint(kGUIPoint2 p) {m_points.SetEntry(m_numpoints++,p);}
private:
	kGUIHTMLObj *m_tag;
	unsigned int m_type;
	unsigned int m_numpoints;
	Array<kGUIPoint2>m_points;
	bool m_haslink;
	kGUIHTMLLinkObj m_linkobj;
};

/*! HTML map class, used to hold clickable areas on images
    @ingroup kGUIHTMLObjects */
class kGUIHTMLMap
{
public:
	kGUIHTMLMap() {m_areas.Init(4,4);Init();}
	void Init(void) {m_numareas=0;}
	void SetTag(kGUIHTMLObj *tag) {m_tag=tag;}
	kGUIHTMLObj *GetTag(void) {return m_tag;}
	kGUIHTMLArea *AddArea(kGUIHTMLObj *atag,unsigned int type) {kGUIHTMLArea *a;a=m_areas.GetEntryPtr(m_numareas++);a->Init(type);a->SetTag(atag);return a;}
	unsigned int GetNumAreas(void) {return m_numareas;}
	kGUIHTMLArea *GetArea(unsigned int n) {return m_areas.GetEntryPtr(n);}
private:
	unsigned int m_numareas;
	kGUIHTMLObj *m_tag;
	ClassArray<kGUIHTMLArea>m_areas;
};

enum
{
RULE_TRUE,
RULE_MAYBE
};

typedef struct
{
	unsigned int m_status;
	kGUIHTMLRule *m_rule;
	unsigned int m_owner;
}RCE_DEF;

typedef struct
{
	kGUIHTMLRule *m_rule;
	unsigned int m_owner;
	bool m_block;
}RO_DEF;

/*! HTML rule cache class, used to cache rule evaluation results for optimization
    @ingroup kGUIHTMLObjects */
class kGUIHTMLRuleCache
{
public:
	kGUIHTMLRuleCache() {m_num=0;m_valid=false;}
	void SetIsValid(bool v) {m_valid=v;}
	bool GetIsValid(void) {return m_valid;}
	void Alloc(int num) {m_num=num;m_rlist.Alloc(num);}
	unsigned int GetNum(void) {return m_num;}
	void SetEntry(unsigned int index,RCE_DEF rce) {m_rlist.SetEntry(index,rce);}
	RCE_DEF *GetRuleListPtr(void) {return m_rlist.GetArrayPtr();}
private:
	bool m_valid:1;
	unsigned int m_num:16;
	Array<RCE_DEF>m_rlist;
};

/*! HTML item cache entry
    @ingroup kGUIHTMLObjects */
class kGUIHTMLItemCacheEntry
{
public:
	void SetURL(kGUIString *s) {m_url.SetString(s);}
	void SetFilename(kGUIString *s) {m_filename.SetString(s);}
	void SetExpires(kGUIString *s) {m_expires.Setz(s->GetString());}
	void SetLastModified(kGUIString *s) {m_lastmod.SetString(s);}
	void SetSize(unsigned int size) {m_size=size;}
	void SetHeader(kGUIString *s) {m_header.SetString(s);}
	kGUIString *GetURL(void) {return &m_url;}
	kGUIString *GetFilename(void) {return &m_filename;}
	void GetExpires(kGUIString *s) {return m_expires.ShortDateTime(s,true);}
	kGUIDate *GetExpires(void) {return &m_expires;}
	kGUIString *GetLastModified(void) {return &m_lastmod;}
	kGUIString *GetHeader(void) {return &m_header;}
	unsigned int GetSize(void) {return m_size;}
	bool GetHasExpired(void) {kGUIDate now;now.SetToday();return now.GetDiffSeconds(&m_expires)<0;}
private:
	kGUIString m_url;
	kGUIString m_filename;
	kGUIString m_lastmod;
	kGUIString m_header;
	kGUIDate m_expires;
	unsigned int m_size;
};

/* this is the cache object for caching downloaded urls to the */
/* hard drive cache directory */

enum
{
CACHEMODE_SAVE,
CACHEMODE_SESSION,
CACHEMODE_NOSAVE
};

/*! HTML item cache entry container
    @ingroup kGUIHTMLObjects */
class kGUIHTMLItemCache
{
public:
	kGUIHTMLItemCache();
	~kGUIHTMLItemCache();

	void SetMode(unsigned int mode) {m_mode=mode;}
	void SetMaxSize(unsigned int size) {m_maxsize=size*(1024*1024);}	/* in MB */
	void CheckCacheSize(void);
	void SetDirectory(const char *dir);
	void Load(kGUIXMLItem *root);

	/* this returns the filename of a valid cache item */
	bool Find(kGUIString *url,kGUIString *fn,kGUIString *header);
	/* this returns true if the item is in the cache but is expired */
	bool FindExpired(kGUIString *url,kGUIString *fn,kGUIString *ifmod);
	/* this is called after an items was downloaded to add it to the cache */
	void Add(kGUIString *url,kGUIString *expires,kGUIString *lastmod,DataHandle *dh);
	/* if an item is expired then this is called if it is still up to date */
	void UpdateExpiry(kGUIString *url,kGUIString *expires);

	/* removes item from cache */
	void Purge(kGUIString *url);

	void Delete(void);
	void Save(kGUIXMLItem *root);
	static int Sort(const void *v1,const void *v2);
private:
	int m_mode;					/* cachemode */
	unsigned int m_maxsize;		/* max size of items currently in the cache */
	unsigned int m_size;		/* total size of items currently in the cache */
	bool m_saved:1;				/* was this saved before exiting? */
	kGUIString m_cachedir;		/* directory to put cached items */
	Hash m_itemcache;			/* disk cache for downloaded items */
	kGUIMutex m_busymutex;
};

/*! HTML visited cache entry
    @ingroup kGUIHTMLObjects */
class kGUIHTMLVisitedCacheEntry
{
public:
	void SetURL(kGUIString *s) {m_url.SetString(s);}
	void SetVisited(kGUIString *s) {m_visited.SetString(s);}
	kGUIString *GetURL(void) {return &m_url;}
	kGUIString *GetVisited(void) {return &m_visited;}
private:
	kGUIString m_url;
	kGUIString m_visited;
};

/*! HTML visited cache entry container
    @ingroup kGUIHTMLObjects */
class kGUIHTMLVisitedCache
{
public:
	kGUIHTMLVisitedCache();
	~kGUIHTMLVisitedCache();
	void SetNumDays(int numdays) {m_numdays=numdays;}
	void Load(kGUIXMLItem *root);
	bool Find(kGUIString *url);
	void Add(kGUIString *url);
	void Save(kGUIXMLItem *root);
	void Delete(kGUIDate *date);
private:
	int m_numdays;
	Hash m_visitedcache;
};

/*! HTML settings, used for user customizable settings
    @ingroup kGUIHTMLObjects */
class kGUIHTMLSettings
{
public:
	kGUIHTMLSettings() {m_usecss=true;m_useusercss=true;m_drawboxes=false;m_drawareas=false;m_areacolor=DrawColor(255,255,255);}
	void Load(kGUIXMLItem *group);
	void Save(kGUIXMLItem *group);

	bool GetUseCSS(void) {return m_usecss;}
	void SetUseCSS(bool u) {m_usecss=u;}

	bool GetUseUserCSS(void) {return m_useusercss;}
	void SetUseUserCSS(bool u) {m_useusercss=u;}

	kGUIString *GetUserCSS(void) {return &m_usercss;}
	void SetUserCSS(kGUIString *ucss) {m_usercss.SetString(ucss);}

	bool GetDrawBoxes(void) {return m_drawboxes;}
	void SetDrawBoxes(bool db) {m_drawboxes=db;}

	bool GetDrawAreas(void) {return m_drawareas;}
	void SetDrawAreas(bool da) {m_drawareas=da;}
private:
	bool m_drawboxes:1;
	bool m_drawareas:1;
	bool m_usecss:1;
	bool m_useusercss:1;
	kGUIString m_usercss;
	kGUIColor m_areacolor;
};

/* this is used to keep a listing of named links within a page, so when a "local" link */
/* is clicked it can calc the y offset to the local link */
class kGUIHTMLLocalLinkObj
{
public:
	void SetNameID(unsigned int id) {m_nameid=id;}
	void SetObj(kGUIHTMLObj *obj) {m_obj=obj;}
	unsigned int GetNameID(void) {return m_nameid;}
	kGUIHTMLObj *GetObj(void) {return m_obj;}
private:
	unsigned int m_nameid;
	kGUIHTMLObj *m_obj;
};

/*! HTML page object
    @ingroup kGUIHTMLObjects */
class kGUIHTMLPageObj: public kGUIContainerObj
{
	friend class kGUIHTMLObj;
public:
	kGUIHTMLPageObj();
	~kGUIHTMLPageObj();

	/* these are needed for a drawable object */
	void Draw(void);
	bool UpdateInput(void);
	void CalcChildZone(void);
	void UpdateScrollBars(void);
	void Preview(void);

	void PurgeRules(void);
	void GetCorrectedSource(kGUIString *cs);
	void PreProcess(kGUIString *tci,kGUIHTMLObj *obj);

	void SetMedia(kGUIString *media) {m_curmedia.SetString(media);}
	kGUIString *GetURL(void) {return &m_url;}
	void MakeURL(kGUIString *parent,kGUIString *in,kGUIString *out);
	void InvalidateTCICache(void);
	void PurgeTCICache(void);

	void SetTrueApplied(kGUIStyleObj *slist,unsigned int owner);
	bool GetTrueBlocked(kGUIStyleObj *slist,unsigned int owner);

#if 1
	//debugging
	void GetTagDesc(kGUIHTMLObj *obj,kGUIString *ts);
	void TraceBack(kGUIHTMLObj *obj);

	void SavePosition(void) {m_rootobject->SavePosition();}
	void ComparePosition(void) {m_rootobject->ComparePosition();}
#endif

	/* debug info */
	void GetCSS(kGUIString *dest) {return dest->SetString(&m_css);}
	void GetCorrectedCSS(kGUIString *dest);
	kGUIString *GetScripts(void) {return &m_scripts;}
	kGUIString *GetMedia(void) {return &m_media;}
	kGUIString *GetErrors(void) {return &m_errors;}
	kGUIString *GetDebug(void) {return &m_debug;}

	void SetURL(kGUIString *url);
	void SetBaseURL(kGUIString *url);
	void SetTarget(kGUIString *target) {m_target.SetString(target);}
	void SetSource(kGUIString *url,kGUIString *source,kGUIString *type,kGUIString *header);
	void SaveInput(Hash *input);	/* add all input form names/values to the hash table */
	void SaveInput(Hash *input,kGUIHTMLFormObj *form,int childnum,kGUIHTMLObj *obj);
	void LoadInput(Hash *input);	/* Load all input form values from the hash table */
	void LoadInput(Hash *input,kGUIHTMLFormObj *form,int childnum,kGUIHTMLObj *obj);
	void SetTitle(kGUIString *title) {m_title.SetString(title);}
	void SetStatusLine(kGUIString *status) {m_status=status;}
	void SetSaveDirectory(const char *dir) {m_savedir.SetString(dir);}
	const char *GetSaveDirectory(void) {return m_savedir.GetString();}

	void SetSettings(kGUIHTMLSettings *s) {m_settings=s;}
	kGUIHTMLSettings *GetSettings(void) {return m_settings;}

	void SetItemCache(kGUIHTMLItemCache *c) {m_itemcache=c;}
	kGUIHTMLItemCache *GetItemCache(void) {return m_itemcache;}

	void SetVisitedCache(kGUIHTMLVisitedCache *c) {m_visitedcache=c;}
	kGUIHTMLVisitedCache *GetVisitedCache(void) {return m_visitedcache;}

	void SetAuthHandler(kGUIDownloadAuthenticateRealms *ah) {m_ah=ah;}
	kGUIDownloadAuthenticateRealms *GetAuthHandler(void) {return m_ah;}

	/* todo, make this changeable */
	bool ClassUseCase(void) {return true;}

	kGUIHTMLMap *LocateMap(kGUIString *name);

	void RemoveComments(kGUIString *s);
	void Parse(bool doprint);
	bool Parse(kGUIHTMLObj *parent,const char *htmlstart,int htmllen,kGUIString *header);
	bool AllWhite(kGUIString *s);
	void CalcPlace(const char *start,const char *place,int *pline,int *pcol);
	void AddDefaultRules(void);
	void InitPosition(void);
	void Position(void);
	int PositionPrint(int width);
	void DrawPrint(int offx,int offy) {m_rootobject->SetChildScrollX(offx);m_rootobject->SetChildScrollY(offy);m_rootobject->Draw();}
	bool GetNoCloseNeeded(void) {return m_nocloseneeded;}
	void SetNoCloseNeeded(bool c) {m_nocloseneeded=c;}
	kGUIString *GetTitle(void) {return &m_title;}
	int GetPopIndex(void) {return m_srnum;}
	void PushStyle(int numbytes,void *data);
	void PopStyles(int index);

	void BuildOwnerRules(void);
	void ApplyStyleRules(kGUIHTMLObj *ho);

	void InitClassStyles(void);
	void AddClassStyles(unsigned int baseowner,unsigned int priority,kGUIString *url,kGUIString *string);
	void AddClassStyle(unsigned int baseowner,unsigned int priority,kGUIString *url,kGUIString *name,kGUIString *value);
	void PurgeClassStyles(void);

	void SetTextDecoration(int d) {m_textdecoration|=d;}
	unsigned int GetTextDecoration(void) {return m_textdecoration;}

	/* called when user adjusts the window size */
	void RePosition(bool reparse) {if(reparse)Parse(false);m_reposition=true;}

	/* called when user has clicked on a link */
	void Click(kGUIString *url,kGUIString *referrer);

	/* this is debug code */
	/* position and print output for 1 frame */
	bool GetTrace(void) {return m_trace;}
	void TraceLayout(void) {m_trace=true;Position();m_trace=false;}
	void TraceDraw(void) {m_trace=true;Dirty();}
//	void TraceDraw(void) {SavePosition();Position();ComparePosition();m_trace=true;Dirty();}

	int GetScrollY(void);
	void SetScrollY(int y);

	void FixCodes(kGUIString *s);
	bool DigOnly(kGUIString *s);
	bool DigOnlyPP(kGUIString *s,bool *percent);
	bool GetColor(kGUIString *col,kGUIHTMLColor *c);

	static int GetHexNibble(const char *hex);
	static int GetHexByte(const char *hex);
	kGUIOnlineImage *LocateImage(kGUIString *url,kGUIString *referrer);
	kGUIOnlineLink *LocateLink(kGUIString *url,kGUIString *referer,unsigned int type,kGUIString *media);
	kGUIHTMLRule *LocateRule(kGUIString *string);
	void AddPossibleRules(void);
	void AddPossibleRules(kGUIHTMLObj *o);
	void RemovePossibleRules(kGUIHTMLObj *o);

	void SetDrawLinkUnder(kGUIString *dlu) {m_drawlinkunder=dlu;}
	void SetClickCallback(void *codeobj,void (*code)(void *,kGUIString *,kGUIString *,kGUIString *)) {m_clickcallback.Set(codeobj,code);}
	void SetIconCallback(void *codeobj,void (*code)(void *,DataHandle *)) {m_iconcallback.Set(codeobj,code);}
	void CallClickCallback(kGUIString *url,kGUIString *ref,kGUIString *post) {m_clickcallback.Call(url,ref,post);}

	void AddMedia(kGUIString *url);
	void FlushCurrentMedia(void);	/* flush all media references on current page */

	int GetConstID(const char *string);

	void SetPID(int pid) {m_pid=pid;}
	int GetPID(void) {return m_pid;}

	CALLBACKGLUEPTR(kGUIHTMLPageObj,ImageLoaded,kGUIOnlineImage)
	CALLBACKGLUEPTR(kGUIHTMLPageObj,LinkLoaded,kGUIOnlineLink)

	unsigned int StringToID(kGUIString *s);
	unsigned int StringToIDcase(kGUIString *s);
	kGUIString *IDToString(unsigned int n);

	kGUIString m_parseerrors;
	kGUIString m_csserrors;
	kGUIString m_errors;
	void SetClickObj(kGUIObj *o) {m_clickobj=o;}

	bool ExtractFromHeader(kGUIString *header,const char *prefix,kGUIString *s,unsigned int *poffset=0);
	void Link(kGUIString *linkline);
	void ExpandClassList(unsigned int num);
	void ExpandIDList(unsigned int num);

	unsigned int AddTCI(kGUIString *tci,kGUIHTMLObj *o);
	void RightClick(void);

	unsigned int GetEM(void);
	void CalcEM(void);
	unsigned int GetLH(void);
	void CalcLH(void);

	void FlushRuleCache(void) {PurgeTCICache();}

	/* attach plugins */
	void AddPlugin(kGUIHTMLPluginObj *obj) {m_plugins.SetEntry(m_numplugins++,obj);}

	CALLBACKGLUEPTR(kGUIHTMLPageObj,CheckSubmit,kGUIEvent)
	void CheckSubmit(kGUIEvent *event);

	/* add a local link */
	void AddLocalLink(kGUIString *name,kGUIHTMLObj *obj) {kGUIHTMLLocalLinkObj *ll;ll=m_locallinks.GetEntryPtr(m_numlocallinks++);ll->SetNameID(StringToID(name));ll->SetObj(obj);}
	kGUIHTMLObj *LocateLocalLink(kGUIString *name);

	unsigned int GetStylePriority(void) {return ++m_stylepriority;}
	unsigned int GetStylePriority(unsigned int after);

	static CONSTLIST_DEF **GetConstPtr(kGUIString *s) {return (CONSTLIST_DEF **)m_consthash.Find(s->GetString());}

	kGUIHTMLPosInfo *GetPos(void) {return m_posinfo.GetEntryPtr(m_posindex++);}
	void FreePos(void) {--m_posindex;}

	void IncLoading(void) {++m_numloading;}
	void AsyncLoad(AsyncLoadInfo *ali,bool hipri) {hipri==true?m_hiloadlist.Write(ali):m_loadlist.Write(ali);}
	void DecLoading(void) {--m_numloading;}
	void ImageLoaded(kGUIOnlineImage *image);

	void SetIsOver(bool over) {m_isover=over;}
	void SetLinkHover(kGUIHTMLLinkObj *hover) {m_linkhover=hover;}
	void SetLinkUnder(kGUIString *url) {m_linkunder.SetString(url);}

	unsigned int GetNumIDs(void) {return m_numids;}
	unsigned int GetNumClasses(void) {return m_numclasses;}
	int GetLangID(void) {return m_lang;}

	/* these 3 contain a list of rule pointers that reference the specificed tag/id or class */
	/* this is used to make rules "possible" as tags/ids/classes are encountered in the heiarchy */
	void AttachRuleToTag(unsigned int index,kGUIHTMLRule *rule) {m_tagrules[index].Add(rule);}
	void AttachRuleToID(unsigned int index,kGUIHTMLRule *rule) {m_idrules.GetEntryPtr(index)->Add(rule);}
	void AttachRuleToClass(unsigned int index,kGUIHTMLRule *rule) {m_classrules.GetEntryPtr(index)->Add(rule);}

	ATTLIST_DEF **FindAtt(kGUIString *s) {return (ATTLIST_DEF **)m_atthash.Find(s->GetString());}
	TAGLIST_DEF **FindTag(kGUIString *s) {return (TAGLIST_DEF **)m_taghash.Find(s->GetString());}

	kGUIHTMLObj *GetTargetObj(void) {return m_targetobj;}
	bool GetHasVertScrollBars(void) {return m_usevs;}

	static TAGLIST_DEF m_taglist[];
	static TAGLIST_DEF m_unknowntag;
	static TAGLIST_DEF m_singleobjtag;
	static TAGLIST_DEF m_texttag;
	static TAGLIST_DEF m_imgtag;
	static TAGLIST_DEF m_contenttag;
	static TAGLIST_DEF m_litexttag;		/* list marker when text */
	static TAGLIST_DEF m_lishapetag;	/* list marker when shape */
	static TAGLIST_DEF m_textgrouptag;
	static ATTLIST_DEF m_attlist[];
	static CONSTLIST_DEF m_constlist[];
	static kGUIColor m_colors[];
	static kGUIString m_attstrings[HTMLATT_NUM];
	static POPLIST_DEF m_poplist[];
private:
	void RightClickEvent(kGUIEvent *event);

	CALLBACKGLUEPTR(kGUIHTMLPageObj,ScrollMoveRow,kGUIEvent)
	CALLBACKGLUEPTR(kGUIHTMLPageObj,ScrollMoveCol,kGUIEvent)
	CALLBACKGLUEPTR(kGUIHTMLPageObj,ScrollEvent,kGUIEvent)
	void ScrollMoveRow(kGUIEvent *event) {if(event->GetEvent()==EVENT_AFTERUPDATE)MoveRow(event->m_value[0].i);}
	void ScrollMoveCol(kGUIEvent *event) {if(event->GetEvent()==EVENT_AFTERUPDATE)MoveCol(event->m_value[0].i);}
	void ScrollEvent(kGUIEvent *event) {if(event->GetEvent()==EVENT_MOVED)Scrolled();}

	CALLBACKGLUE(kGUIHTMLPageObj,Scrolled)
	CALLBACKGLUE(kGUIHTMLPageObj,LoadListThread)
	void LoadListThread(void);
	void LinkLoaded(kGUIOnlineLink *link);
	void AttachLink(kGUIOnlineLink *link);
	bool ValidMedia(kGUIString *m);

	CALLBACKGLUE(kGUIHTMLPageObj,TimerEvent)
	void TimerEvent(void);

	void CheckItemCache(kGUIString *url,kGUIString *fn);
	void CacheItem(kGUIString *url,kGUIString *expires,DataHandle *dh);

	const char *Parse(kGUIString *ts,kGUIString *ts2,kGUIHTMLObj *renderparent,kGUIHTMLObj *parent,const char *fp,int level);

	/* cache for tci strings and rule true/possible arrays */
	unsigned int m_tcinumrules;
	Hash m_tcicache;

	int m_lastmousex;
	int m_lastmousey;
	unsigned int m_appliedlevel;
	unsigned int m_applied[HTMLATT_UNKNOWN];
	unsigned int m_trueapplied[HTMLATT_UNKNOWN];
	bool m_poppossrules;

	kGUIHTMLSettings *m_settings;
	kGUIHTMLItemCache *m_itemcache;
	kGUIHTMLVisitedCache *m_visitedcache;
	kGUIDownloadAuthenticateRealms *m_ah;

	unsigned int m_numplugins;
	Array<kGUIHTMLPluginObj *>m_plugins;

	unsigned int m_numlocallinks;
	ClassArray<kGUIHTMLLocalLinkObj>m_locallinks;

	kGUIString m_defstyle;
	int m_lang;			/* page language using stringtoid to convert back to a string */
	kGUIString m_savedir;
	kGUIString m_savefn;
	
	kGUIMenuColObj m_popmenu;
	kGUIObj *m_clickobj;
	void SaveAs(kGUIFileReq *req,int closebutton);
	void AskOverwrite(int closebutton);
	void DoSaveAs(void);
	CALLBACKGLUEPTR(kGUIHTMLPageObj,RightClickEvent,kGUIEvent)
	CALLBACKGLUEPTR(kGUIHTMLPageObj,DoPopMenu,kGUIEvent)
	CALLBACKGLUEPTRVAL(kGUIHTMLPageObj,SaveAs,kGUIFileReq,int)
	CALLBACKGLUEVAL(kGUIHTMLPageObj,AskOverwrite,int)
	void DoPopMenu(kGUIEvent *event);

	void MoveRow(int delta);
	void MoveCol(int delta);
	void Scrolled(void);

	static bool m_hashinit;
	static Hash m_taghash;		/* hash list for tags */
	static Hash m_atthash;		/* hash list for attributes */
	static Hash m_consthash;	/* hash list for constants */
	static Hash m_pophash;	/* hash list for constants */
	Hash m_rulehash;	/* hash list for page style rules */

	/* array of rule pointers that reference the tags */
	int m_curtagrefs[HTMLTAG_NUMTAGS];
	kGUIHTMLRuleList m_tagrules[HTMLTAG_NUMTAGS];

	/* array of encountered counts for each class id */
	unsigned int m_numclasses;
	Array<int> m_curclassrefs;
	ClassArray<kGUIHTMLRuleList> m_classrules;

	/* array of encountered counts for each class id */
	unsigned int m_numids;
	Array<int> m_curidrefs;
	ClassArray<kGUIHTMLRuleList> m_idrules;

	/* array of map areas */
	unsigned int m_nummaps;
	ClassArray<kGUIHTMLMap> m_maps;

	/* pointer to array of all text objects with "blink" */
	unsigned int m_numblinks;
	int m_blinkdelay;
	Array<kGUIHTMLTextObj *> m_blinks;

	/* this is a generic string to enumerated ID class used to convert strings to numbers */
	/* it is used for ID and ClASSES and any other string that is easier to use as a number */
	unsigned int m_nextstoid;
	Hash m_stoidhash;		/* enumerated hash list for ids */
	ClassArray<kGUIString>m_idtos;

	/* this contains a pointer to each rule and it is sorted so the most important rule is at the top */
	unsigned int m_numrules;
	Array<kGUIHTMLRule *>m_rules;

	/* this is a duplicate of the numrules list above, except that it contains expanded entries for */
	/* each author level, for example, it contains all valid rules at the userimportant level, then */
	/* all valid rules at the authorimportant level, then author, then user then system */
	bool m_ownerrulesbuilt;
	unsigned int m_numownerrules;
	Array<RO_DEF>m_ownerrules;

	kGUIHTMLObj *m_rootobject;
	kGUIHTMLObj *m_absobject;
	kGUIString m_title;
	kGUIScrollBarObj m_hscrollbar;
	kGUIScrollBarObj m_vscrollbar;
	kGUIScroll m_scroll;

	kGUIHTMLAttrib *m_beforecontent;
	kGUIHTMLAttrib *m_aftercontent;

//	kGUIString m_screenmedia;
//	kGUIString m_printmedia;
	kGUIString m_curmedia;	/* current one */

	bool m_strict:1;
	bool m_usehs:1;
	bool m_usevs:1;
	bool m_singlemode:1;		/* true when displaying a single object ( image or movie etc ) */
	bool m_tracerules:1;
	bool m_trace:1;
	bool m_trackpossiblerules:1;
	bool m_copytdc:1;				/* copy text-color to text-decoration-color flag */
	bool m_isover:1;

	int m_srnum;
	int m_srdataindex;
	Array<STYLERESTORE_DEF>m_srlist;
	Array<unsigned char>m_srdata;

	/* external places */
	kGUIString *m_drawlinkunder;
	kGUIString m_linkunder;
	kGUIString *m_status;

	/* used for user viewing to debug page problems */
	kGUIString m_css;
	kGUIString m_scripts;
	kGUIString m_media;
	kGUIString m_debug;
	Hash m_mediahash;

	kGUIString m_type;	/* type: 'text/html', 'img/jpeg', 'text' etc... */
	kGUIString m_header;	/* used for objects linked in the header */
	kGUIString m_url;
	kGUIString m_target;
	kGUIHTMLObj *m_targetobj;
	kGUIString m_urlroot;
	kGUIString m_urlbase;
	const char *m_fp;
	int m_len;
	unsigned int m_pageem;
	kGUIString m_refreshurl;
	int m_refreshdelay;

	/* table settings */
	int m_cellspacing;
	int m_cellpadding;

	unsigned int m_whitespace;
	unsigned int m_texttransform;
	unsigned int m_textdecoration;
	unsigned int m_textalign;
	unsigned int m_dir;
	kGUIUnits m_lineheightratio;
	int m_pagelineheightpix;

	int m_textshadowr;
	int m_textshadowx;
	int m_textshadowy;
	kGUIHTMLColor m_textshadowcolor;
	unsigned int m_liststyle;
	unsigned int m_liststyleposition;
	unsigned int m_liststyleurl;
	unsigned int m_liststyleurlreferer;

	int m_fontid;
	kGUIHTMLColor m_fontcolor;
	kGUIColor m_textdecorationcolor;
	kGUIUnits m_textindent;
	kGUIUnits m_letterspacing;
	kGUIUnits m_wordspacing;

	unsigned int m_posindex;
	ClassArray<kGUIHTMLPosInfo>m_posinfo;

	double m_fontscale;
	
	double m_fontsize;
	int m_fontweight;

	kGUIHTMLLinkObj *m_link;
	kGUIHTMLObj *m_form;
	bool m_nocloseneeded;
	int m_mode;
	int m_pagew;	/* size after scroll bar space is subtracted */
	int m_pageh;

	/* link object that cursor is hovering over */
	kGUIHTMLLinkObj *m_linkhover;

	/* alternating list of hover objects */
	int m_hovertoggle;
	unsigned int m_hoverlistsize[2];
	Array<kGUIHTMLObj *>m_hoverlist[2];

	bool m_reposition;	/* set then images are loaded and page needs to be re-positioned */

	bool m_iconlinked;
	/* style groups, first styles attached to HTML tags */
//	kGUIStyleObj m_tagstyles[HTMLTAG_NUMTAGS];
	/* next, style groups for user classes */
//	int m_numclassstyles;
//	Array<kGUIStyleObj *>m_classstyles;
//	Hash m_classstylehash;		/* hash list for styleclasses */

	/* linked objects on this page */
//	int m_numlinkedobjects;
//	Array<kGUIHTMLObj *>m_linkedobjects;

	/*****************************************************************/

	int m_numloading;
	int m_numskipped;

	/* images that are loaded */
	unsigned int m_numimages;
	Hash m_imagehash;		/* hash list for url -> image */
	Array<kGUIOnlineImage *>m_images;

	int m_pid;

	/* linked items that are loaded */
	unsigned int m_numlinks;
	Hash m_linkhash;			/* quick has table to locate entry */
	Array<kGUIOnlineLink *>m_links;

	unsigned int m_stylepriority;

	kGUICallBackPtrPtrPtr<kGUIString,kGUIString,kGUIString>m_clickcallback;
	kGUICallBackPtr<DataHandle>m_iconcallback;

	volatile bool m_shutdown;
	volatile bool m_loadreset;
	kGUIThread m_loadthread;

	/* high priority items like css/html are added to this one */
	kGUICommStack<AsyncLoadInfo>m_hiloadlist;
	/* lower priority items like images etc are added to this one */
	kGUICommStack<AsyncLoadInfo>m_loadlist;
};

#endif
