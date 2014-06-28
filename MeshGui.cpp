#include <string>
#include "MeshGui.h"

// IDs for each control
enum CtrlId
{
	LIGHT0_ENABLE,
	LIGHT1_ENABLE,
	LIGHT0_INTENSITY,
	LIGHT1_INTENSITY,
	SHADING_MODE,
	ENABLE_ID,
	DISABLE_ID,
	SHOW_ID,
	HIDE_ID,
	INPUT_FILE,
	OPEN_MESH,
	SAVE_MESH,
	EDGE_NUMBER,
	DECIMATE
};

// shared variables between main programs and control callbacks
int MeshGui::light0_enabled = 1;
int MeshGui::light1_enabled = 1;
float MeshGui::light0_intensity = 1.0;
float MeshGui::light1_intensity = .4;
float MeshGui::xy_aspect;
float MeshGui::scale = 1.0;
// the default mesh file
char MeshGui::filetext[sizeof(GLUI_String)] = "sphere"; // cube0 eight bigsmile horse sphere
char MeshGui::filename[] = "smf/sphere.smf";
// text for debugging
int MeshGui::show_text = false;
const char *MeshGui::string_list[] = { "Hello World!", "Foo", "Testing...", "Bounding box: on" };
int MeshGui::curr_string = 0;
GLUI_Spinner *MeshGui::light0_spinner, *MeshGui::light1_spinner;

int MeshGui::main_window;
float MeshGui::mesh_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float MeshGui::view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float MeshGui::obj_pos[] = { 0.0, 0.0, 0.0 };

int MeshGui::edge_number = 2;

// initialization of SMF model
Decimator MeshGui::smf_model(MeshGui::filename);
//Subdivision MeshGui::subd(MeshGui::filename);

// constructor
MeshGui::MeshGui(void)
{}
// main entrance
int MeshGui::run(int argc, char *argv[])
{
	// debug
	//std::cout << smf_model << std::endl;
	//subd.subdivide();
	//std::cout << subd << std::endl;
	this->initGlut(argc, argv);
	this->initGlui();
	this->initGl();
	return EXIT_SUCCESS;
}
// initialize GLUT
int MeshGui::initGlut(int argc, char *argv[])
{
	// init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	main_window = glutCreateWindow("smf_view");
	// set glut callback
	glutDisplayFunc(display);
	GLUI_Master.set_glutReshapeFunc(reshape);  
	GLUI_Master.set_glutKeyboardFunc(keyboard);
	GLUI_Master.set_glutSpecialFunc(NULL);
	GLUI_Master.set_glutMouseFunc(mouse);
	glutMotionFunc(motion);
}
// initialize GLUI
int MeshGui::initGlui(void)
{
	// create the side subwindow
	GLUI *glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);

	// radio button group
	GLUI_RadioGroup *ot_group = new GLUI_RadioGroup (glui, &radiogroup_item_id, SHADING_MODE, control_cb);
	// shading choices
	glui->add_radiobutton_to_group( ot_group, "flatShaded" );
	glui->add_radiobutton_to_group( ot_group, "smoothShaded" );
	glui->add_radiobutton_to_group( ot_group, "wireframe" );
	glui->add_radiobutton_to_group( ot_group, "shadedEdges" );
	glui->add_radiobutton_to_group( ot_group, "point" );
	// load and save smf file
	new GLUI_EditText (glui, "smf/", GLUI_EDITTEXT_TEXT, filetext, INPUT_FILE, control_cb);
	new GLUI_Button( glui, "open", OPEN_MESH, control_cb );
	new GLUI_Button( glui, "save", SAVE_MESH, control_cb );
	// A 'quit' button
	new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );

	// some controls for lights
	//GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", false);
	GLUI_Panel *light0 = new GLUI_Panel( glui, "Light 0" );
	GLUI_Panel *light1 = new GLUI_Panel( glui, "Light 1" );
	new GLUI_Checkbox( light0, "Enabled", &light0_enabled, LIGHT0_ENABLE, control_cb );
	light0_spinner = new GLUI_Spinner( light0, "Intensity:", &light0_intensity, LIGHT0_INTENSITY, control_cb );
	light0_spinner->set_float_limits( 0.0, 1.0 );
	GLUI_Scrollbar *sb;
	sb = new GLUI_Scrollbar( light0, "Red",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[0],LIGHT0_INTENSITY,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light0, "Green",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[1],LIGHT0_INTENSITY,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light0, "Blue",GLUI_SCROLL_HORIZONTAL, &light0_diffuse[2],LIGHT0_INTENSITY,control_cb);
	sb->set_float_limits(0,1);
	new GLUI_Checkbox( light1, "Enabled", &light1_enabled, LIGHT1_ENABLE, control_cb );
	light1_spinner = new GLUI_Spinner( light1, "Intensity:", &light1_intensity, LIGHT1_INTENSITY, control_cb );
	light1_spinner->set_float_limits( 0.0, 1.0 );
	sb = new GLUI_Scrollbar( light1, "Red",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[0],LIGHT1_INTENSITY,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light1, "Green",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[1],LIGHT1_INTENSITY,control_cb);
	sb->set_float_limits(0,1);
	sb = new GLUI_Scrollbar( light1, "Blue",GLUI_SCROLL_HORIZONTAL, &light1_diffuse[2],LIGHT1_INTENSITY,control_cb);
	sb->set_float_limits(0,1);

	GLUI_Spinner *edge_spinner = new GLUI_Spinner(glui, "EdgeNumber", &edge_number, EDGE_NUMBER, control_cb );
	edge_spinner->set_float_limits(2, 100);
	new GLUI_Button(glui, "decimate", DECIMATE, control_cb );

	// Link windows to GLUI, and register idle callback
	glui->set_main_gfx_window( main_window );

	// Create the bottom subwindow
	GLUI *glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );
	// rotate the world
	GLUI_Rotation *view_rot = new GLUI_Rotation(glui2, "Objects", view_rotate );
	view_rot->set_spin( 1.0 );
	// rotate the model
	new GLUI_Column( glui2, false );
	GLUI_Rotation *sph_rot = new GLUI_Rotation(glui2, "Model", mesh_rotate );
	sph_rot->set_spin( .98 );
	// rotate the blue light
	new GLUI_Column( glui2, false );
	GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2, "Blue Light", lights_rotation );
	lights_rot->set_spin( .82 );
	// object XY translate
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
	trans_xy->set_speed( .005 );
	// object X translate
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_x = new GLUI_Translation(glui2, "Objects X", GLUI_TRANSLATION_X, obj_pos );
	trans_x->set_speed( .005 );
	// object Y translate
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
	trans_y->set_speed( .005 );
	// object y translate
	new GLUI_Column( glui2, false );
	GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .005 );

	return EXIT_SUCCESS;
}

// default lights
GLfloat MeshGui::light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat MeshGui::light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat MeshGui::light0_position[] = {.5f, .5f, 1.0f, 0.0f};
GLfloat MeshGui::light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat MeshGui::light1_diffuse[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat MeshGui::light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};
GLfloat MeshGui::lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
// initialize GL
int MeshGui::initGl(void)
{
	// default shade type
	glShadeModel(GL_FLAT);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	// set up OpenGL lights
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
	// enable z-bufferring
	glEnable(GL_DEPTH_TEST);
	// start the main loop
	glutMainLoop();
	return EXIT_SUCCESS;
}
void MeshGui::display(void)
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

	switch (radiogroup_item_id)
	{
	case 2:
		// draw the smf model
		glPushMatrix();
		glTranslatef( -.5, 0.0, 0.0 );
		glMultMatrixf( mesh_rotate );
		glColor3f(0.9f, 0.9f, 0.9f);

		smf_model.display();
		//subd.display();

		glPopMatrix();
		break;
	// shade with mesh edges displayed
	case 3:
		// the mesh itself
		glPushMatrix();
		glTranslatef( -.5, 0.0, 0.0 );
		glMultMatrixf( mesh_rotate );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glColor3f(0.9f, 0.9f, 0.9f);

		smf_model.display();

		glPopMatrix();
		// the edges
		glPushMatrix();
		glTranslatef( -.5, 0.0, 0.0 );
		glMultMatrixf( mesh_rotate );
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0f, 0.0f, 0.0f);

		smf_model.display();

		glColor3f(0.9f, 0.9f, 0.9f);
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		break;
	case 1:
	default:
		// draw the smf model
		glPushMatrix();
		glTranslatef( -.5, 0.0, 0.0 );
		glMultMatrixf( mesh_rotate );
		glColor3f(0.9f, 0.9f, 0.9f);

		smf_model.display();
		//subd.display();

		glPopMatrix();
		break;
	}

	/*glPushMatrix();
	glTranslatef( .5, 0.0, 0.0 );
	glMultMatrixf( mesh_rotate );
	glutSolidTorus( .15,.3,16,8 );
	glPopMatrix();*/

	// show text
	if (show_text) 
	{
		// disable lighting while we render text
		glDisable( GL_LIGHTING );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, 100.0, 0.0, 100.0  );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glColor3ub( 0, 0, 0 );
		glRasterPos2i( 10, 10 );
		// render the live character array 'text'
		for(int i=0; i<(int)strlen( string_list[curr_string] ); i++ )
		{
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, string_list[curr_string][i] );
		}
	}
	glEnable( GL_LIGHTING );
	glutSwapBuffers(); 
}
void MeshGui::reshape( int x, int y )
{
	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;
	glutPostRedisplay();
}
void MeshGui::keyboard(unsigned char Key, int x, int y)
{
	switch(Key)
	{
	case 27: // quit
	case 'q':
		exit(0);
		break;
	};
	glutPostRedisplay();
}
void MeshGui::mouse(int button, int button_state, int x, int y )
{
}
void MeshGui::motion(int x, int y )
{
	//glutPostRedisplay(); 
}
void MeshGui::idle( void )
{
	// According to the GLUT specification, the current window is undefined during an idle callback.  So we need to explicitly change it if necessary
	if ( glutGetWindow() != main_window )
	{
		glutSetWindow(main_window);
	}
	// GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this application
	glutPostRedisplay();
}
// GLUI control callback
void MeshGui::control_cb( int control )
{
	float v[4];
	switch (control)
	{
	case LIGHT0_ENABLE:
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
	case LIGHT1_ENABLE:
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
	case LIGHT0_INTENSITY:
		v[0] = light0_diffuse[0] * light0_intensity;
		v[1] = light0_diffuse[1] * light0_intensity;
		v[2] = light0_diffuse[2] * light0_intensity;
		v[3] = light0_diffuse[3];
		glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
		break;
	case LIGHT1_INTENSITY:
		v[0] = light1_diffuse[0] * light1_intensity;
		v[1] = light1_diffuse[1] * light1_intensity;
		v[2] = light1_diffuse[2] * light1_intensity;
		v[3] = light1_diffuse[3];
		glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
		break;
	case SHADING_MODE:
		switch (radiogroup_item_id)
		{
		case 1: // smoothShaded
			glShadeModel(GL_SMOOTH);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case 2: // wireframe
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 3: // shadedEdges
			glShadeModel(GL_FLAT);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case 4: // point
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			break;
		case 0: // flatShaded
		default:
			glShadeModel(GL_FLAT);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		}
		break;
	case INPUT_FILE:
		strcpy(filename, "smf/");
		strcat(filename, filetext);
		strcat(filename, ".smf");
		break;
	case OPEN_MESH:
		smf_model.loadFile(filename);
		glutPostRedisplay();
		std::cout << "loadFile " << filename << std::endl;
		break;
	case SAVE_MESH:
		std::cout << "saving file " << filename << std::endl;
		smf_model.save(filename);
		break;
	case EDGE_NUMBER:
		break;
	case DECIMATE:
		std::cout << "decimate with edge " << edge_number << std::endl;
		smf_model.decimate(edge_number);
		//std::cout << smf_model << std::endl;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
