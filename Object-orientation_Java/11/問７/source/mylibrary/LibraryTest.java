package	mylibrary;
import	mypub.*;
import	java.util.*;
import	java.util.Random;

public class LibraryTest{  //�����_���Ɏؗp�ƕԋp�����ALibrary�̏󋵂��݂�
	public static void main(String[] args){
		Library	lib=new	Library();



		try{
			Book	b=new	Book("0000000000001","�������I�j�����q����","���󖜑�","GA����",1996);
			lib.addList(b);
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			Magazine m=new	Magazine("0000000000017","������l�͍��点����", "�W�p��",1,1,1996);
		}

		catch(Exception	e){
			System.out.println(e);
		}





		int	Array_number;	//���Ԗڂ̗v�f����\���ϐ�
		int	i=0;		//����؂�ĕԋp���邩�̃J�E���^�[�ϐ�
		int	kaguya;		//magazine�̊����̃J�E���^�[�ϐ�


		try{
			lib.addList(new	Book("0000000000002","SAO","�쌴�I","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		
		try{
			lib.addList(new	Book("0000000000002","SAO","�쌴�I","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}



		try{
			lib.addList(new	Book("0000000000003","����̓]���r�ł����H","�ؑ��S��","�x�m�����[",-1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000004111","�X�g���C�N��U��u���b�h","�O�_�x�l","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new	Book("0000000000005","�]��������X���C����������","����","�}�C�N���}�K�W��",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000006","���̑f���炵�����E�ɏj����","�łȂ�","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000007","�Ƃ��閂�p�̋֏��ژ^","���r�a�n","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000008","��e�̃A���A","�ԏ����w","���f�B�A�t�@�N�g���[",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
		lib.addList(new	Book("0000000000009","��F�̌���","�R�i����h�C��","�V������",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new Magazine("0000000000010","�E���{���X", "�V����",11,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{				
			lib.addList(new Magazine("0000000000011","���̑��", "�u�k��",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
		lib.addList(new Magazine("0000000000012","To LOVE��", "�W�p��",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new Magazine("0000000000013","To LOVE��@�_�[�N�l�X", "�W�p��",21,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new Magazine("0000000000014","�A�J�����a��I", "�X�N�G�A�E�G�j�b�N�X",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new Magazine("0000000000015","�߂����{�b�N�X", "�W�p��",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
		lib.addList(new Magazine("0000000000016","�����ω���", "�W�p��",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}



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
