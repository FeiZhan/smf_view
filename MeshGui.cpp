#include "MeshGui.h"
#include "SmfModel.h"

float xy_aspect;
int   last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;

// These are the live variables passed into GLUI
int   wireframe = 0;
int   obj_type = 1;
int   segments = 8;
int   segments2 = 8;
int   light0_enabled = 1;
int   light1_enabled = 1;
float light0_intensity = 1.0;
float light1_intensity = .4;
int   main_window;
float scale = 1.0;
int   show_sphere=1;
int   show_torus=1;
int   show_axes = 1;
float sphere_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float torus_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };

//  Id of the selected radio button
int radiogroup_item_id = 0;

char filetext[sizeof(GLUI_String)] = "eight";
char filename[] = "smf/eight.smf";
SmfModel smf_model(filename);

// text
int   show_text = false;
const char *string_list[] = { "Hello World!", "Foo", "Testing...", "Bounding box: on" };
int   curr_string = 0;

// Pointers to the windows and some of the controls we'll create
GLUI *glui, *glui2;
GLUI_Spinner    *light0_spinner, *light1_spinner;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;

// User IDs for callbacks
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#define RADIOGROUP_ID  270
#define ENABLE_ID            300
#define DISABLE_ID           301
#define SHOW_ID              302
#define HIDE_ID              303
#define OPENFILE_ID				400
#define OPENMESH_ID				410
#define SAVEMESH_ID				420

GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position[] = {.5f, .5f, 1.0f, 0.0f};
GLfloat light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};
GLfloat lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

// GLUI control callback
void control_cb( int control )
{
	float v[4];
	switch (control)
	{
	case LIGHT0_ENABLED_ID:
		if ( light0_enabled )
		{
			glEnable( GL_LIGHT0 );
			light0_spinner->enable();
		}
		else
		{
			glDisable( GL_LIGHT0 ); 
			light0_spinner->disable();
		}
		break;
	case LIGHT1_ENABLED_ID:
		if ( light1_enabled )
		{
			glEnable( GL_LIGHT1 );
			light1_spinner->enable();
		}
		else
		{
			glDisable( GL_LIGHT1 ); 
			light1_spinner->disable();
		}
		break;
	case LIGHT0_INTENSITY_ID:
		v[0] = light0_diffuse[0] * light0_intensity;
		v[1] = light0_diffuse[1] * light0_intensity;
		v[2] = light0_diffuse[2] * light0_intensity;
		v[3] = light0_diffuse[3];
		glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
		break;
	case LIGHT1_INTENSITY_ID:
		v[0] = light1_diffuse[0] * light1_intensity;
		v[1] = light1_diffuse[1] * light1_intensity;
		v[2] = light1_diffuse[2] * light1_intensity;
		v[3] = light1_diffuse[3];
		glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
		break;
	case ENABLE_ID:
		glui2->enable();
		break;
	case DISABLE_ID:
		glui2->disable();
		break;
	case SHOW_ID:
		glui2->show();
		break;
	case HIDE_ID:
		glui2->hide();
		break;
	case RADIOGROUP_ID:
		switch (radiogroup_item_id)
		{
		case 0: // flatShaded
			glShadeModel(GL_FLAT);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case 1: // smoothShaded
			glShadeModel(GL_SMOOTH);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case 2: // wireframe
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 3: // shadedEdges
			glShadeModel(GL_SMOOTH);
			glDepthFunc(GL_LEQUAL); 
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		default:
			break;
		}
		break;
	case OPENFILE_ID:
		strcpy(filename, "smf/");
		strcat(filename, filetext);
		strcat(filename, ".smf");
		break;
	case OPENMESH_ID:
		smf_model.loadFile(filename);
		glutPostRedisplay();
		std::cout << "loadFile " << filename << std::endl;
		break;
	case SAVEMESH_ID:
		std::cout << "saving file " << filename << std::endl;
		smf_model.save(filename);
		break;
	default:
		break;
	}
}
void draw_axes( float scale )
{
	glDisable( GL_LIGHTING );
	glPushMatrix();
	glScalef( scale, scale, scale );
	glBegin( GL_LINES );
	glColor3f( 1.0, 0.0, 0.0 );
	glVertex3f( .8f, 0.05f, 0.0 );  glVertex3f( 1.0, 0.25f, 0.0 ); /* Letter X */
	glVertex3f( 0.8f, .25f, 0.0 );  glVertex3f( 1.0, 0.05f, 0.0 );
	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 1.0, 0.0, 0.0 ); /* X axis      */
	glColor3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 1.0, 0.0 ); /* Y axis      */
	glColor3f( 0.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 1.0 ); /* Z axis    */
	glEnd();
	glPopMatrix();
	glEnable( GL_LIGHTING );
}

void myGlutDisplay(void)
{
	glClearColor( .9f, .9f, .9f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 15.0 );

	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	glMultMatrixf( lights_rotation );
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -2.6f );
	glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] ); 
	glMultMatrixf( view_rotate );

	glScalef( scale, scale, scale );

	// Now we render object, using the variables 'obj_type', 'segments', and 'wireframe'.  These are _live_ variables, which are transparently updated by GLUI

	glPushMatrix();
	glTranslatef( -.5, 0.0, 0.0 );
	glMultMatrixf( sphere_rotate );
	if ( wireframe && show_sphere)
	{
		//glutWireSphere( .4, segments, segments );
		smf_model.display();
	}
	else if ( show_sphere )
	{
		//glutSolidSphere( .4, segments, segments );
		smf_model.display();
	}
	if ( show_axes )
		draw_axes(.52f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef( .5, 0.0, 0.0 );
	glMultMatrixf( torus_rotate );
	if ( wireframe && show_torus )
	{
		glutWireTorus( .15,.3,16,segments );
	}
	else if ( show_torus )
	{
		glutSolidTorus( .15,.3,16,segments );
	}
	if ( show_axes )
	{
		draw_axes(.52f);
	}
	glPopMatrix();

	if ( show_text ) 
	{
		// Disable lighting while we render text
		glDisable( GL_LIGHTING );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, 100.0, 0.0, 100.0  );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glColor3ub( 0, 0, 0 );
		glRasterPos2i( 10, 10 );
		// Render the live character array 'text'
		for(int i=0; i<(int)strlen( string_list[curr_string] ); i++ )
		{
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, string_list[curr_string][i] );
		}
	}

	glEnable( GL_LIGHTING );

	glutSwapBuffers(); 
}
void myGlutReshape( int x, int y )
{
	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;
	glutPostRedisplay();
}
void myGlutKeyboard(unsigned char Key, int x, int y)
{
	switch(Key)
	{
	case 27: 
	case 'q':
		exit(0);
		break;
	};
	glutPostRedisplay();
}
void myGlutMouse(int button, int button_state, int x, int y )
{
}
void myGlutMotion(int x, int y )
{
	//glutPostRedisplay(); 
}
void myGlutIdle( void )
{
	// According to the GLUT specification, the current window is undefined during an idle callback.  So we need to explicitly change it if necessary
	if ( glutGetWindow() != main_window )
	{
		glutSetWindow(main_window);
	}
	// GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this application
	glutPostRedisplay();
}

int MeshGui::run(void)
{
	// Set up OpenGL lights
	glEnable(GL_LIGHTING);
	glEnable( GL_NORMALIZE );
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// Enable z-buferring
	glEnable(GL_DEPTH_TEST);

	this->initGlui();

	return EXIT_SUCCESS;
}
int MeshGui::initGlui(void)
{
	//printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );
	// Create the side subwindow
	glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
	obj_panel = new GLUI_Rollout(glui, "Properties", false );

	// Control for object params
	new GLUI_Checkbox( obj_panel, "Wireframe", &wireframe, 1, control_cb );
	GLUI_Spinner *spinner = new GLUI_Spinner( obj_panel, "Segments:", &segments);
	spinner->set_int_limits( 3, 60 );
	spinner->set_alignment( GLUI_ALIGN_RIGHT );
	GLUI_Spinner *scale_spinner = new GLUI_Spinner( obj_panel, "Scale:", &scale);
	scale_spinner->set_float_limits( .2f, 4.0 );
	scale_spinner->set_alignment( GLUI_ALIGN_RIGHT );

	// some controls for lights
	GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", false );
	GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Light 1" );
	GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Light 2" );
	new GLUI_Checkbox( light0, "Enabled", &light0_enabled, LIGHT0_ENABLED_ID, control_cb );
	light0_spinner = new GLUI_Spinner( light0, "Intensity:", &light0_intensity, LIGHT0_INTENSITY_ID, control_cb );
	light0_spinner->set_float_limits( 0.0, 1.0 );
	GLUI_Scrollbar *sb;
	sb = new GLUI_Scrollbar( light0, "Red",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[0],LIGHT0_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light0, "Green",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[1],LIGHT0_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light0, "Blue",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[2],LIGHT0_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);
	new GLUI_Checkbox( light1, "Enabled", &light1_enabled, LIGHT1_ENABLED_ID, control_cb );
	light1_spinner = new GLUI_Spinner( light1, "Intensity:", &light1_intensity, LIGHT1_INTENSITY_ID, control_cb );
	light1_spinner->set_float_limits( 0.0, 1.0 );
	sb = new GLUI_Scrollbar( light1, "Red",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[0],LIGHT1_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light1, "Green",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[1],LIGHT1_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light1, "Blue",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[2],LIGHT1_INTENSITY_ID,control_cb);
	sb->set_float_limits(0,1);

	// Add another rollout
	GLUI_Rollout *options = new GLUI_Rollout(glui, "Options", true );
	new GLUI_Checkbox( options, "Draw sphere", &show_sphere );
	new GLUI_Checkbox( options, "Draw torus", &show_torus );
	new GLUI_Checkbox( options, "Draw axes", &show_axes );
	//new GLUI_Checkbox( options, "Draw text", &show_text );

	// Add listbox
	/*new GLUI_StaticText( glui, "" );
	GLUI_Listbox *list = new GLUI_Listbox( glui, "Text:", &curr_string );
	for(int i=0; i<4; i++ )
	{
		list->add_item( i, string_list[i] );
	}
	new GLUI_StaticText( glui, "" );*/

	//  Create radio button group
	GLUI_RadioGroup *ot_group = glui->add_radiogroup_to_panel (obj_panel, &radiogroup_item_id, RADIOGROUP_ID, control_cb);
	//  Add the radio buttons to the radio group
	glui->add_radiobutton_to_group( ot_group, "flatShaded" );
	glui->add_radiobutton_to_group( ot_group, "smoothShaded" );
	glui->add_radiobutton_to_group( ot_group, "wireframe" );
	glui->add_radiobutton_to_group( ot_group, "shadedEdges" );

	new GLUI_EditText (glui, "smf/", GLUI_EDITTEXT_TEXT, filetext, OPENFILE_ID, control_cb);
	new GLUI_Button( glui, "open", OPENMESH_ID, control_cb );
	new GLUI_Button( glui, "save", SAVEMESH_ID, control_cb );

	// Disable/Enable buttons
	new GLUI_Button( glui, "Disable movement", DISABLE_ID, control_cb );
	new GLUI_Button( glui, "Enable movement", ENABLE_ID, control_cb );
	new GLUI_Button( glui, "Hide", HIDE_ID, control_cb );
	new GLUI_Button( glui, "Show", SHOW_ID, control_cb );
	new GLUI_StaticText( glui, "" );

	// A 'quit' button
	new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );

	// Link windows to GLUI, and register idle callback
	glui->set_main_gfx_window( main_window );

	// Create the bottom subwindow
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );
	GLUI_Rotation *view_rot = new GLUI_Rotation(glui2, "Objects", view_rotate );
	view_rot->set_spin( 1.0 );
	new GLUI_Column( glui2, false );
	GLUI_Rotation *sph_rot = new GLUI_Rotation(glui2, "Sphere", sphere_rotate );
	sph_rot->set_spin( .98 );
	new GLUI_Column( glui2, false );
	GLUI_Rotation *tor_rot = new GLUI_Rotation(glui2, "Torus", torus_rotate );
	tor_rot->set_spin( .98 );
	new GLUI_Column( glui2, false );
	GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2, "Blue Light", lights_rotation );
	lights_rot->set_spin( .82 );
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
	trans_xy->set_speed( .005 );
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_x = new GLUI_Translation(glui2, "Objects X", GLUI_TRANSLATION_X, obj_pos );
	trans_x->set_speed( .005 );
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
	trans_y->set_speed( .005 );
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .005 );

#if 0
	// We register the idle callback with GLUI, *not* with GLUT
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
#endif

	return EXIT_SUCCESS;
}
