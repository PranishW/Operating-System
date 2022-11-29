#!/bin/sh
createFile()
{
	echo "Enter filename :-"
	read filename
	touch $filename
	echo "File $filename successfully created\n"
}
displayRecords()
{
	echo "Enter filename :-"
	read filename
	res=`ls | grep $filename | wc -w`
	if [ $res -gt 0 ]
	then
		echo "Name\tMobile\tAddress\tPincode\n"
		cat $filename
	else
		echo "File not found\n"
	fi
}
insertRecords()
{
	echo "Enter name,mobile no,address,pincode :-"
	read name mob_no address pin
	chk=`cat $filename | grep $mob_no | wc -w`
	if [ $chk -gt 0 ]
	then
		echo "Mobile no alrady exists"
	else
		printf "%10s %10s %10s %06s\n" $name $mob_no $address $pin >> $filename
		echo "Record inserted successfully\n"
	fi
}
modifyRecord()
{
	echo "Enter mobile no"
	read mob_no1
	chk=`cat $filename | grep $mob_no1 | wc -w`
	if [ $chk -gt 0 ]
	then
		echo "Record found\n"
		echo "Enter name,mobile no,address,pincode"
		read name mob_no address pin
		new=`echo $name $mob_no $address $pin`
		old=`cat $filename | grep $mob_no1`
		sed -i s/"$old"/"$new"/g $filename
		echo "Record Modified Successfully\n"
	else
		echo "Record does not exist\n"
	fi
}
deleteRecord()
{
	echo "Enter mobile no"
	read mob_no;
	chk=`cat $filename | grep $mob_no | wc -w`
	if [ $chk -gt 0 ]
	then
		echo "Record found\n"
		sed -i /$mob_no/d $filename
		echo "Record deleted successfully\n"
	else
		echo "Record does not exist\n"
	fi
}
main()
{
	while [ true ]
	do
		echo "\n1. Create a File\n"
		echo "2. Display Records\n"
		echo "3. Insert a Record\n"
		echo "4. Delete a Record\n"
		echo "5. Modify a Record\n"
		echo "6. Exit\n"
		echo "Enter file operation"
		read op
		case $op in
		1)
			createFile ;;
	       	2)
			displayRecords ;;
		3)
			insertRecords ;;
		4)
			deleteRecord ;;
		5)
			modifyRecord ;;
		6)
			echo "Exiting from File operations\n"
			exit ;;
		esac
	done
}
main
