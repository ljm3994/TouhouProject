#pragma once

/*
�̱��� ������ staic member�� �ϳ��� �ν��Ͻ��� �����Ǹ�
���α׷� �ȿ��� ���������� ������ �����ϴ�
������ Ŭ������ �ν��Ͻ��� �ϳ��� ���� �ϰ��� �Ҷ� ����Ѵ�

���� ������ �̿��ص� �ϳ��� �ν��Ͻ��� �����Ҽ� ������
�̱��� ������ ����ϸ� Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ���
�����ϴ� ����� ĸ��ȭ �Ͽ� �����Ҽ� �ְ�
��ü ���� �Ҹ� �ν��Ͻ� ���� ���� ��� Ȱ�뿡 �����ϴ�
*/

template <typename T>
class SingletonBase 
{	
protected:
	static T* Instance;

	SingletonBase() {};
	~SingletonBase() {};
public:
	static T* GetInstance();
	void ReleaseSingleton();


};

template <typename T>
T* SingletonBase<T>::Instance = nullptr;

//inline �Լ� ��ũ�� �Լ� �ñ��ϸ� �˻�

template<typename T>
T * SingletonBase<T>::GetInstance()
{
	if (!Instance)Instance = new T;
	return Instance;
}

template<typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
