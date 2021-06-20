#include "..\headers\Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertexPath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		string Line = "";
		while (getline(VertexShaderStream, Line)) {
			VertexShaderCode += "\n" + Line;
		}
		VertexShaderStream.close();
	}
	else {
		cerr << "ERROR::VERTEX_SHADER::FILE_NOT_OPENED at: " << vertexPath << endl;
		exit(-1);
	}

	int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* VertexSource = VertexShaderCode.c_str();

	glShaderSource(VertexShader, 1, &VertexSource, NULL);
	glCompileShader(VertexShader);

	// Check Compile Errors
	int success;
	char infolog[512];

	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(VertexShader, 512, NULL, infolog);
		cerr << "ERROR::VERTEX_SHADER::COMPILE_FAILURE\n" << infolog << endl;
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragmentPath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		string Line = "";
		while (getline(FragmentShaderStream, Line)) {
			FragmentShaderCode += "\n" + Line;
		}
		FragmentShaderStream.close();
	}
	else {
		cerr << "ERROR::FRAGMENT_SHADER::FILE_NOT_OPENED at: " << fragmentPath << endl;
		exit(-1);
	}

	int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* FragmentSource = FragmentShaderCode.c_str();

	glShaderSource(FragmentShader, 1, &FragmentSource, NULL);
	glCompileShader(FragmentShader);

	// Check Compile Errors
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(FragmentShader, 512, NULL, infolog);
		cerr << "ERROR::FRAGMENT_SHADER::COMPILE_FAILURE\n" << infolog << endl;
	}

	// Read Geometry Shader code from the file (if it exists)
	unsigned int GeometryShader;
	if (geometryPath != nullptr) {
		string GeometryShaderCode;
		ifstream GeometryShaderStream(geometryPath, std::ios::in);
		if (GeometryShaderStream.is_open()) {
			string Line = "";
			while (getline(GeometryShaderStream, Line)) {
				GeometryShaderCode += "\n" + Line;
			}
			GeometryShaderStream.close();
		}
		else {
			cerr << "ERROR::GEOMETRY_SHADER::FILE_NOT_OPENED at: " << geometryPath << endl;
			exit(-1);
		}

		GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* GeometrySource = GeometryShaderCode.c_str();
		glShaderSource(GeometryShader, 1, &GeometrySource, NULL);

		// Check Compile Errors
		glGetShaderiv(GeometryShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(GeometryShader, 512, NULL, infolog);
			cerr << "ERROR::GEOMETRY_SHADER::COMPILE_FAILURE\n" << infolog << endl;
		}
	}

	ID = glCreateProgram();
	// Attach Shaders
	glAttachShader(ID, VertexShader);
	glAttachShader(ID, FragmentShader);
	if (geometryPath != nullptr) {
		glAttachShader(ID, GeometryShader);
	}
	glLinkProgram(ID);

	// Check for Linking Errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << endl;
	}

	// Detach Shaders
	glDetachShader(ID, VertexShader);
	glDetachShader(ID, FragmentShader);
	if (geometryPath != nullptr) {
		glDetachShader(ID, GeometryShader);
	}

	// Delete Shaders
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	if (geometryPath != nullptr) {
		glDeleteShader(GeometryShader);
	}
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::UseShader() {
	glUseProgram(ID);
}

void Shader::SetInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec3(const string& name, vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetBool(const string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetViewMatrix(mat4 viewMatrix) {
	int viewMatrixLocation = glGetUniformLocation(ID, "viewMatrix");
	if (viewMatrixLocation == -1) {
		cerr << "SHADER::SET_VIEW_MATRIX::UNIFORM_NOT_FOUND" << endl;
	}
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Shader::SetProjectionMatrix(mat4 projectionMatrix) {
	int projectionMatrixLocation = glGetUniformLocation(ID, "projectionMatrix");
	if (projectionMatrixLocation == -1) {
		cerr << "SHADER::SET_PROJECTION_MATRIX::UNIFORM_NOT_FOUND" << endl;
	}
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Shader::SetWorldMatrix(mat4 worldMatrix) {
	int worldMatrixLocation = glGetUniformLocation(ID, "worldMatrix");
	if (worldMatrixLocation == -1) {
		cerr << "SHADER::SET_WORLD_MATRIX::UNIFORM_NOT_FOUND" << endl;
	}
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}
