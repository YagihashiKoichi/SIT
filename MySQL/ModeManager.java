/**
 *ModeManager
 *���ꂼ��̃N���X�̃C���X�^���X�𐶐����A�T�[�r�X���j���[�ꗗ�̒����烆�[�U�[�̑I�������@�\�𔻕ʂ���N���X�ł���B
 *@author �R�؏~�O
 *modified by Koichi.Yagihashi
 *�C���X�^���X�̐�����while�̊O�ōs���悤�ɕύX
 *�A�v���P�[�V�������I���������ۂ̕�����ǉ�
 *�A�v���P�[�V�����̎g�p�𑱂��邩�ǂ������������e�@�\������Ō�̂P�ɓ���
 *����ɔ������̃��\�b�h���폜
 *switch����break�̒ǉ�
 *�S�Ă̈�����萔����W�����͂ɕύX
 *�ǉ��ɑΉ����镶��ǉ�
 */

import java.io.*;

public class ModeManager{
	public static void main(String[] args) {
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		Anime b = new Anime();
		
		AbstractUpdater r1 = new UpdateReview();
		AbstractExecuter r2 = new ExecuteReview();
		
		AbstractUpdater u1 = new UpdateURL();
		AbstractUpdater u2 = new UpdateOfficeAddress();
		AbstractUpdater u3 = new UpdateOfficeNumber();
		AbstractUpdater u4 = new UpdateCompanyAddress();
		AbstractUpdater u5 = new UpdateCompanyNumber();
		AbstractUpdater u6 = new UpdateBroadcasterAddress();
		
		AbstractDeleter d1 = new DeleteService();
		AbstractDeleter d2 = new DeleteAnime();
		
		AbstractAdder a1 = new AddService();
		AbstractAdder a2 = new AddBroadcaster();
		AbstractAdder a3 = new AddSinger();
		
		AbstractAdder a4 = new AddMusic();
		AbstractAdder a5 = new AddAnime();
		AbstractAdder a6 = new AddOriginal();
		AbstractAdder a7 = new AddAuthor();
		AbstractAdder a8 = new AddRadioActor();
		AbstractAdder a9 = new AddOffice();
		AbstractAdder a10 = new AddCompany();
		
		String pass;
		String set,where;
		String value1,value2,value3;
		int last=1;
		
		try{
			while(last==1){
					
				System.out.println("=== �A�j�����Ǘ��A�v���P�[�V���� ===");
				System.out.println("�ȉ��̒�������s�������T�[�r�X���j���[�̔ԍ�����ЂƂI�����Ă��������F");
				System.out.println("1�F�A�j������������");
				System.out.println("2�F�A�j���̕]���܂��͉{��������");
				System.out.println("3�F�f�[�^�̍X�V������");
				System.out.println("4�F�f�[�^�̍폜������");
				System.out.println("5�F�f�[�^�̒ǉ�������");
			
				int select_number = Integer.parseInt(reader.readLine());
					
				switch(select_number) {
					case 1:
						b.bigSearch();
						break;
								
					case 2:
						System.out.println("�]�����]���̉{����I�����Ă�������");
						System.out.println("1:�]�� / 2:�]���̉{��");
						int review_number = Integer.parseInt(reader.readLine());
						
						switch(review_number){
							case 1:
								System.out.println("�]���������A�j���^�C�g������͂��Ă��������B");
								where=reader.readLine();
								
								while(true){
									System.out.println("1����5�͈̔͂̐����ŕ]������͂��Ă��������B");
									set = reader.readLine();
									if(set.equals("1")||set.equals("2")||set.equals("3")||set.equals("4")||set.equals("5"))
											break;
								}
								r1.SetAndUpdate(where,set);
								break;
								
							case 2:
								r2.queryAndShow();
								break;
								
							default:
								System.out.println("�ԍ����s���ł�");
								break;
						}
						break;
								
					case 3:
						System.out.println("�p�X���[�h����͂��Ă�������");//�f�[�^�̕ҏW���ނ�݂ɍs�����Ƃ��ł��Ȃ��悤��
						pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("���O�C������\n");
							System.out.println("�ȉ��̒�����X�V���������̂̔ԍ���I�����Ă��������F");
							System.out.println("1�F�z�M�T�[�r�X��URL");
							System.out.println("2�F�������̏Z��");
							System.out.println("3�F�������̓d�b�ԍ�");
							System.out.println("4�F�����Ђ̖{�ЏZ��");
							System.out.println("5�F�����Ђ̓d�b�ԍ�");
							System.out.println("6�F�����ǂ̏Z��");
								
							int upnumber = Integer.parseInt(reader.readLine());
							switch(upnumber) {
								case 1:
									System.out.println("URL��ύX�������T�[�r�X������͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX���URL����͂��Ă��������B");
									set = reader.readLine();
									u1.SetAndUpdate(where,set);
									break;
							
								case 2: 
									System.out.println("�Z����ύX������������������͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX��̏Z������͂��Ă��������B");
									set = reader.readLine();
									u2.SetAndUpdate(where,set);
									break;
								
								case 3: 
									System.out.println("�d�b�ԍ���ύX������������������͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX��̓d�b�ԍ�����͂��Ă��������B");
									set = reader.readLine();
									u3.SetAndUpdate(where,set);
									break;
						
								case 4: 
									System.out.println("�Z����ύX�����������Ж�����͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX��̏Z������͂��Ă��������B");
									set = reader.readLine();
									u4.SetAndUpdate(where,set);
									break;	
										
								case 5: 
									System.out.println("�d�b�ԍ���ύX�����������Ж�����͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX��̓d�b�ԍ�����͂��Ă��������B");
									set = reader.readLine();
									u5.SetAndUpdate(where,set);
									break;
									
								case 6:
									System.out.println("�Z����ύX�����������ǖ�����͂��Ă�������");
									where = reader.readLine();
									System.out.println("�ύX��̏Z������͂��Ă��������B");
									set = reader.readLine();
									u6.SetAndUpdate(where,set);
									break;
										
								default:
									System.out.println("�ԍ����s���ł�");
									break;
							}
						}else
							System.out.println("���O�C�����s\n�p�X���[�h���Ԉ���Ă��܂�");
						break;
						
					case 4:			
						System.out.println("�p�X���[�h����͂��Ă�������");//�f�[�^�̍폜���ނ�݂ɍs�����Ƃ��ł��Ȃ��悤��
					    pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("���O�C������\n");
							System.out.println("�ȉ��̒�����폜���������̂̔ԍ���I�����Ă��������F");
							System.out.println("1�F�z�M�T�[�r�X");
							System.out.println("2�F�A�j��");
							
							int delnumber = Integer.parseInt(reader.readLine());
									
							switch(delnumber){
								case 1:
									System.out.println("�폜�������z�M�T�[�r�X������͂��Ă�������");
									where = reader.readLine();
									d1.SetAndDelete(where);
									break;
									
								case 2:
									System.out.println("�폜�������A�j���̃^�C�g������͂��Ă�������");
									where = reader.readLine();
									d2.SetAndDelete(where);
									break;
					
								default:
									System.out.println("�ԍ����s���ł�");
									break;
							}
						} else 
							System.out.println("���O�C�����s\n�p�X���[�h���Ԉ���Ă��܂�");
						break;
						
					case 5:
						System.out.println("�p�X���[�h����͂��Ă�������");//�f�[�^�̒ǉ����ނ�݂ɍs�����Ƃ��ł��Ȃ��悤��
						pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("���O�C������\n");
							System.out.println("�ȉ��̒�����ǉ����������̂̔ԍ���I�����Ă��������F");
							System.out.println("1�F�z�M�T�[�r�X");
							System.out.println("2�F������");
							System.out.println("3�F�̎�");
							System.out.println("4�F��");
							System.out.println("5�F�A�j��");
							System.out.println("6�F����");
							System.out.println("7�F�����");
							System.out.println("8�F���D");
							System.out.println("9�F������");
							System.out.println("10�F������");
							
							int addnumber = Integer.parseInt(reader.readLine());
							switch(addnumber) {
									
								case 1:
									System.out.println("�ǉ��������T�[�r�X������͂��Ă��������B");
									value1 = reader.readLine();
									System.out.println("�ǉ��������T�[�r�X��URL����͂��Ă��������B");
									value2 = reader.readLine();									
									a1.SetAndAdd(value1,value2);
									break;
								
								case 2:
									System.out.println("�ǉ������������ǂ���͂��Ă��������B");
									value1 = reader.readLine();
									System.out.println("�ǉ������������ǂ̏Z������͂��Ă��������B");
									value2 = reader.readLine();
									a2.SetAndAdd(value1,value2);
									break;
									
								case 3:
									System.out.println("�ǉ��������̎薼����͂��Ă��������B");
									value1 = reader.readLine();	
									a3.SetAndAdd(value1);
									break;
										
								case 4:
									System.out.println("�ǉ��������Ȗ�����͂��Ă��������B");
									value1 = reader.readLine();
									a4.SetAndAdd(value1);
									break;
								
								case 5:
									System.out.println("�ǉ��������A�j���̃^�C�g������͂��Ă��������B");
									value1 = reader.readLine();
									a5.SetAndAdd(value1);
									break;
										
								case 6:
									System.out.println("�ǉ�����������̃^�C�g������͂��Ă��������B");
									value1 = reader.readLine();
									a6.SetAndAdd(value1);
									break;
									
								case 7:
									System.out.println("�ǉ�����������Җ�����͂��Ă��������B");
									value1 = reader.readLine();
									a7.SetAndAdd(value1);
									break;
									
								case 8:
									System.out.println("�ǉ����������D�̖��O����͂��Ă��������B");
										value1 = reader.readLine();
									while(true){
										System.out.println("�ǉ����������D�̐��ʂ�'�j��'��'����'�œ��͂��Ă��������B");
										value2 = reader.readLine();
										if(value2.equals("�j��")||value2.equals("����"))
											break;
									}
									a8.SetAndAdd(value1,value2);
									break;
										
								case 9:
									System.out.println("�ǉ�������������������͂��Ă��������B");
									value1 = reader.readLine();
									System.out.println("�ǉ��������������̓d�b�ԍ�����͂��Ă��������B");
									value2 = reader.readLine();
									System.out.println("�ǉ��������������̏Z������͂��Ă��������B");
									value3 = reader.readLine();
									a9.SetAndAdd(value1,value2,value3);
									break;
										
								case 10:
									System.out.println("�ǉ������������Ж�����͂��Ă��������B");
									value1 = reader.readLine();
									System.out.println("�ǉ������������Ђ̖{�ЏZ������͂��Ă��������B");
									value2 = reader.readLine();
									System.out.println("�ǉ������������Ђ̓d�b�ԍ�����͂��Ă��������B");
									value3 = reader.readLine();
									a10.SetAndAdd(value1,value2,value3);
									break;
									
								default:
									System.out.println("�ԍ����s���ł�");
									break;
							}
					} else
						System.out.println("���O�C�����s\n�p�X���[�h���Ԉ���Ă��܂�");
					break;
					
				default:
					System.out.println("�ԍ����s���ł�");
					break;
				}
				
				System.out.println("�܂��A�v���P�[�V�����𗘗p���܂����H");
				System.out.println("1:YES / 0:NO");
				last = Integer.parseInt(reader.readLine());
			}
			System.out.println("�����p���肪�Ƃ��������܂����B");
		} catch (IOException e) {
			System.out.println("IO Error: " + e.toString() + e.getMessage());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}	
}
