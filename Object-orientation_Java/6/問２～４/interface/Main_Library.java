import	java.util.*;
import	java.util.Random;

public class Main_Library{  //�����_���Ɏؗp�ƕԋp�����ALibrary�̏󋵂��݂�
	public static void main(String[] args){
		Book b = new Book("�������I�j�����q����","���󖜑�","GA����");		Magazine m = new Magazine("������l�͍��点����", "�W�p��",1,1);		Library	lib=new	Library();

		int	Array_number;	//���Ԗڂ̗v�f����\���ϐ�
		int	i=0;		//����؂�ĕԋp���邩�̃J�E���^�[�ϐ�
		int	kaguya;		//magazine�̊����̃J�E���^�[�ϐ�

		lib.AddList(new	Book("SAO","�쌴�I","KADOKAWA"));
		lib.AddList(new	Book("����̓]���r�ł����H","�ؑ��S��","�x�m�����["));
		lib.AddList(new	Book("�X�g���C�N��U��u���b�h","�O�_�x�l","KADOKAWA"));
		lib.AddList(new	Book("�]��������X���C����������","����","�}�C�N���}�K�W��"));
		lib.AddList(new	Book("���̑f���炵�����E�ɏj����","�łȂ�","KADOKAWA"));
		lib.AddList(new	Book("�Ƃ��閂�p�̋֏��ژ^","���r�a�n","KADOKAWA"));
		lib.AddList(new	Book("��e�̃A���A","�ԏ����w","���f�B�A�t�@�N�g���["));
		lib.AddList(new	Book("��F�̌���","�R�i����h�C��","�V������"));

		for(kaguya=2;kaguya<=12;kaguya++){	//12���܂ō쐬
			lib.AddList(new Magazine("������l�͍��点����", "�W�p��",kaguya,1));
		}



		while(true){	//�����_���Ŏ؂�Ă���
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.GetArrayList().size()){
				lib.GetArrayList().get(Array_number).lent();
				//System.out.println(lib.GetArrayList().get(Array_number));
				//�m�F�p
				i++;
			}

			if(i==10)	break;
		}

		i=0;

		while(true){	//�����_���ŕԂ�
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.GetArrayList().size()){
				lib.GetArrayList().get(Array_number).returned();				//System.out.println(lib.GetArrayList().get(Array_number));
				//�m�F�p
				i++;
			}

			if(i==10)	break;
		}

		for(int	s=0;s<lib.GetArrayList().size();s++) //���݂�Library�̏�Ԃ�\��
		{
			System.out.println(lib.GetArrayList().get(s));
		}
	}
}
