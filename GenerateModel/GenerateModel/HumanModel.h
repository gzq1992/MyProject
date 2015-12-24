#ifndef _HUMAN_MODEL_H
#define _HUMAN_MODEL_H
#include "stdafx.h"
#include "Boundary.h"
#if 0
struct HumanHead{
	Eigen::MatrixXi HeadVertices;
	Eigen::MatrixXi HeadFaces;
	size_t NumberOfHeadVertices;
	size_t NumberOfHeadFaces;
};
struct HumanBody{
	Eigen::MatrixXi BodyVertices;
	Eigen::MatrixXi BodyFaces;
	size_t NumberOfBodyVertices;
	size_t NumberOfBodyFaces;
};
#endif

struct HumanPart{
	Eigen::MatrixXd Vertices;
	Eigen::MatrixXi Faces;
	Eigen::MatrixXd Colors;
	size_t NumberOfVertices;
	size_t NumberOfFaces;
	HumanPart() :NumberOfFaces(0), NumberOfVertices(0){}
	void SetVertices(const Eigen::MatrixXd& _Vertices)
	{
		Vertices = _Vertices;
		NumberOfVertices = _Vertices.rows();
	}

	void SetFaces(const Eigen::MatrixXi& _Faces)
	{
		Faces = _Faces;
		NumberOfFaces = _Faces.rows();
	}

	void SetColors(const Eigen::MatrixXd& _Colors)
	{
		Colors = _Colors;
	}
};


class HumanModel
{
public:
	typedef HumanPart HumanHead;
	typedef HumanPart HumanBody;
	enum PartOfHuman{Head,Body,Full};
	//bool ReadFlag;
	HumanModel();
	HumanModel(Eigen::MatrixXd& Vertices, Eigen::MatrixXi& Faces);
	HumanModel(HumanHead& HeadPart, HumanHead& BodyPart,Boundary& NowBoundary);
	~HumanModel();
	void SetHumanModel(Eigen::MatrixXd& Vertices, Eigen::MatrixXi& Faces);		
	//������������ĵ����
	//void ReadSegmentBodyInfo(char* filename);
	//void SetHumanPart(const Eigen::MatrixXd& Vertices, HumanPart& part);
	//void SetHumanPart(const Eigen::MatrixXi& Faces, HumanPart& part);
	//void SetHumanPart(const Eigen::MatrixXd& Vertices, const Eigen::MatrixXi& Faces, const Eigen::MatrixXd& Colors, HumanPart& part);
	void ReadMatlabFile(const char* filename,HumanPart& part);
	//���ڶ�ȡmat��ʽ��head��body�ĵ�����Ϣ
	//void ReadObjFile(const char* filename,HumanPart& part);
	//��ȡobj��ʽ��head��body
	const Eigen::MatrixXd& GetVertices() const
	{
		return HumanFullVertices;
	}
	//��ȡ��ǰmodel�ĵ���Ϣ	HumanFullVertices
	const Eigen::MatrixXi& GetFaces() const
	{
		return HumanFullFaces;
	}
	//��ȡ��ǰmodel������Ϣ	HumanFullFaces
	const Eigen::MatrixXd& GetVertexNormal()const
	{
		return VNormal;
	}
	size_t GetNumberOfVertices() const
	{
		return NumberOfVertices;
	}
	//��ȡ��ǰmodel�ĵ���	NumberOfVertices
	size_t GetNumberOfFaces() const
	{
		return NumberOfFaces;
	}
	//��ȡ��ǰmodel������	NumberOfFaces

	void ComputeNormals();

	void ConvergeHeadAndBody(HumanHead& HeadPart, HumanHead& BodyPart, Boundary& NowBoundary);
	//void TextureOnHead(Eigen::MatrixXd& Colors);
	//void TextureOnBody(Eigen::MatrixXd& Colors);
	//�ں�ͷ�������壬NowBoundary��Ҫ������Ե�����Ϣ
	void SaveModel2Obj(const char* filename);
	void SaveModel2Obj(const char* filename,Eigen::MatrixXd& Vertices,Eigen::MatrixXi& Faces,Eigen::MatrixXd& Normals);
	
	//��ģ�͵���汣���OBJ��ʽ
	//static const int NModel;
	//static Eigen::MatrixXd Time;
	//static int count;
private:
	Eigen::MatrixXd HumanFullVertices;
	//ģ�����еĵ㣨�ںϺ�
	Eigen::MatrixXi HumanFullFaces;
	//ģ�����е��棨�ںϺ�
	Eigen::MatrixXd VNormal;
	//��ķ�����
	Eigen::MatrixXd FNormal;
	//��ķ�����
	Eigen::MatrixXd Colors;
	size_t NumberOfVertices;
	size_t NumberOfFaces;

	double AdjustScale(Eigen::MatrixXd& HeadBoundaryVertices, Eigen::MatrixXd& BodyBoundaryVertices);
	//����ͷ���ĳ߶�
	Eigen::MatrixXd RigidTransformation(Eigen::MatrixXd& HeadBoundaryVertices, Eigen::MatrixXd& BodyBoundaryVertices);
	//����ͷ��������
	void TransformVertices(Eigen::MatrixXd& Vertices,Eigen::MatrixXd R, Eigen::MatrixXd t);
	//����R,t�任�������
	Eigen::MatrixXd InterpolationForConverge(Eigen::MatrixXd CenterVertex_H,Eigen::MatrixXd& CenterVertex_B,Eigen::MatrixXd& Neighbors );
	//�Ա߽���ֵƽ��
	void ConvergeHeadAndBodyStuff(HumanHead& HeadPart, HumanHead& BodyPart, Boundary& NowBoundary);
	//�ں�
	void PlaceHeadAndBodyToModel(HumanHead& HeadPart, HumanBody& BodyPart, Boundary& NowBoundary);
	//�������е���棨��Ҫ�����ںϲ���Ե�㣩
	void AdjustHeadEdgeVertex(HumanHead& HeadPart,Boundary& NowBoundary);

	void _ComputeFaceNormal();
	void _ComputeVertexNormal();
	Eigen::MatrixXd MatrixRowCross(Eigen::MatrixXd& left, Eigen::MatrixXd& right);
};

#endif