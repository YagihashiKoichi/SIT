package	mylibrary;
import	mypub.*;
import	java.util.*;
import	java.util.Random;

public class LibraryTest{  //�����_���Ɏؗp�ƕԋp�����ALibrary�̏󋵂��݂�
	public static void main(String[] args){
		Library	lib=new	Library();
		Book	b=new	Book("�������I�j�����q����","���󖜑�","GA����");
		Magazine m=new	Magazine("������l�͍��点����", "�W�p��",1,1);

		int	Array_number;	//���Ԗڂ̗v�f����\���ϐ�
		int	i=0;		//����؂�ĕԋp���邩�̃J�E���^�[�ϐ�
		int	kaguya;		//magazine�̊����̃J�E���^�[�ϐ�

		lib.addList(b);
		lib.addList(new	Book("SAO","�쌴�I","KADOKAWA"));
		lib.addList(new	Book("����̓]���r�ł����H","�ؑ��S��","�x�m�����["));
		lib.addList(new	Book("�X�g���C�N��U��u���b�h","�O�_�x�l","KADOKAWA"));
		lib.addList(new	Book("�]��������X���C����������","����","�}�C�N���}�K�W��"));
		lib.addList(new	Book("���̑f���炵�����E�ɏj����","�łȂ�","KADOKAWA"));
		lib.addList(new	Book("�Ƃ��閂�p�̋֏��ژ^","���r�a�n","KADOKAWA"));
		lib.addList(new	Book("��e�̃A���A","�ԏ����w","���f�B�A�t�@�N�g���["));
		lib.addList(new	Book("��F�̌���","�R�i����h�C��","�V������"));
		lib.addList(m);
		lib.addList(new Magazine("�E���{���X", "�V����",11,1));				lib.addList(new Magazine("���̑��", "�u�k��",1,1));				lib.addList(new Magazine("To LOVE��", "�W�p��",1,1));				lib.addList(new Magazine("To LOVE��@�_�[�N�l�X", "�W�p��",21,1));		
		lib.addList(new Magazine("�A�J�����a��I", "�X�N�G�A�E�G�j�b�N�X",1,1));
		lib.addList(new Magazine("�߂����{�b�N�X", "�W�p��",1,1));			lib.addList(new Magazine("�����ω���", "�W�p��",1,1));
		while(true){	//�����_���Ŏ؂�Ă���
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.getArrayList().size()){
				lib.getArrayList().get(Array_number).lent();
				//System.out.println(lib.GetArrayList().get(Array_number));
				//�m�F�p
				i++;
			}

			if(i==10)	break;
		}

		i=0;

		while(true){	//�����_���ŕԂ�
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.getArrayList().size()){
				lib.getArrayList().get(Array_number).returned();				//System.out.println(lib.GetArrayList().get(Array_number));
				//�m�F�p
				i++;
			}

			if(i==10)	break;
		}

		lib.libraryHas(); //���݂�Library�̏�Ԃ�\��


/*
//�m�F�p
		for(int	s=0;s<lib.GetArrayList().size();s++) //���݂�Library�̏�Ԃ�\��
		{
			System.out.println(lib.getArrayList().get(s));
		}
*/




		
	}
}
