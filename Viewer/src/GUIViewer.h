#ifndef OTE_VIEWER
#define OTE_VIEWER

#include <iostream>

#include <igl/viewer/Viewer.h>
#include <igl/png/texture_from_file.h>

#include <nanogui/formhelper.h>
#include <nanogui/screen.h>

#include <Eigen/Dense>

#include <MeshDefinition.h>

#include <MeshFormConverter.h>
#include <LineCylinder.h>
#include <MeshMerger.h>
#include <PointSphere.h>

#include <EuclideanOrbifoldSolver.h>
#include <HyperbolicOrbifoldSolver.h>
#include <BFF.h>

#include <Topology\EuclideanCoveringSpace.h>
#include <Topology\HyperbolicCoveringSpace.h>

#include <MeshMarker.h>


enum ShowOption { ORIGINAL, SLICED, EMBEDDING, COVERING_SPACE };

class OTEViewer: public igl::viewer::Viewer
{
public: 
	OTEViewer();
	void Init();
private:
	SurfaceMesh mesh_;
	SurfaceMesh sliced_mesh_;
	MeshMarker marker_;

	std::vector<OpenMesh::VertexHandle> cone_vts_;

	Eigen::MatrixXd V_;
	Eigen::MatrixXd V_normal_;
	Eigen::MatrixXd UV_Z0_; // z equal to zero
	Eigen::MatrixXi F_;
	Eigen::MatrixXd F_normal_;
	Eigen::MatrixXd TC_;
	Eigen::MatrixXd UV_;

	

	// texture RGB channels;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R_;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> G_;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> B_;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> A_;
	
	// Flags
	ShowOption show_option_ = ORIGINAL;
	bool show_boundaries_ = false;
	bool show_slice_ = false;
	bool euclidean_ = false;
	bool hyperbolic_ = false;

	int vertex_index_= 0;
	int slice_start_ = 0;
	int slice_end_ = 0;


protected:

	// Init functions
	void InitMenu();
	void InitKeyboard();

	// IO functions
	void LoadMesh();
	void LoadTexture();
	void SaveMesh();

	void UpdateMeshData(SurfaceMesh &mesh);  
	void UpdateTextureCoordData(SurfaceMesh &mesh);
	void ShowUV();
	void ShowCoveringSpace();

	void ShowHalfedges(SurfaceMesh &mesh, std::vector<OpenMesh::HalfedgeHandle> h_vector);
	void ShowBoundaries(SurfaceMesh &mesh);
	void ShowSliceAndCones();
	void UpdateMeshViewer();


	// Setting slices and singularities
	void SetSlice(int i, int j);
	void SetSingularity(int i);
	


};

#endif