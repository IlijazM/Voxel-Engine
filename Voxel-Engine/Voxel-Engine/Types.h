#pragma once

#include <iostream>

namespace LL {
	typedef struct { float x, y; }			vec2_t;
	typedef struct { float x, y, z; }		vec3_t;
	typedef struct { float x, y, z, w; }	vec4_t;

	typedef struct { unsigned char r, g, b; }		rgb_t;
	typedef struct { unsigned char r, g, b, a; }	rgba_t;

	typedef struct { char nx, ny, nz; }		normals_t;
	typedef struct { char u, v; }			uv_t;
	typedef struct { uint32_t a, b, c; }	indices_t;

	typedef struct {
		vec3_t position;
		rgba_t colors;
		normals_t normals;
		uv_t uvs;
	} vertex_t;

}