#pragma once
class Timer //��ʱ����(��֡ת��Ϊ����Ϊ��λ)
{
private:
	int fps; //ÿ�����֡�����Ĵ��� 60
	int times;//
	int time;//��¼ÿ����6��֡������ʱ�� 100ms
public:
	Timer();
	void run() { //ִ��
		times++;
		if (times>6)
		{
			time++;
			times = 0;
		}
	}
	int getTime(); //����ʱ�� 100ms Ϊ��λ
	~Timer();
};

