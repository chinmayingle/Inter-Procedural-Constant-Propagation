; ModuleID = 'file5.c'
source_filename = "file5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !17 {
entry:
  %l = alloca i32, align 4
  tail call void @llvm.dbg.declare(metadata ptr %l, metadata !22, metadata !DIExpression()), !dbg !23
  store i32 40, ptr %l, align 4, !dbg !23
  call void @fun(i32 noundef 10, i32 noundef 100, i32 noundef 1000), !dbg !24
  call void @bar(i32 noundef 1000, i32 noundef 400, i32 noundef 300), !dbg !25
  %0 = load i32, ptr %l, align 4, !dbg !26
  call void @foo(i32 noundef 100, i32 noundef 400, i32 noundef 1000, i32 noundef %0), !dbg !27
  ret i32 0, !dbg !28
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @fun(i32 noundef %i, i32 noundef %j, i32 noundef %k) #0 !dbg !29 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  %k.addr = alloca i32, align 4
  %o = alloca i32, align 4
  %q = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %i, ptr %i.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %i.addr, metadata !32, metadata !DIExpression()), !dbg !33
  store i32 %j, ptr %j.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %j.addr, metadata !34, metadata !DIExpression()), !dbg !35
  store i32 %k, ptr %k.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %k.addr, metadata !36, metadata !DIExpression()), !dbg !37
  %0 = load i32, ptr %i.addr, align 4, !dbg !38
  call void @bar(i32 noundef 2000, i32 noundef %0, i32 noundef 1000), !dbg !39
  tail call void @llvm.dbg.declare(metadata ptr %o, metadata !40, metadata !DIExpression()), !dbg !41
  %1 = load i32, ptr %i.addr, align 4, !dbg !42
  %mul = mul nsw i32 %1, 2, !dbg !43
  store i32 %mul, ptr %o, align 4, !dbg !41
  tail call void @llvm.dbg.declare(metadata ptr %q, metadata !44, metadata !DIExpression()), !dbg !45
  store i32 2, ptr %q, align 4, !dbg !45
  tail call void @llvm.dbg.declare(metadata ptr %a, metadata !46, metadata !DIExpression()), !dbg !47
  %2 = load i32, ptr %q, align 4, !dbg !48
  %3 = load i32, ptr %o, align 4, !dbg !49
  %mul1 = mul nsw i32 %2, %3, !dbg !50
  %4 = load i32, ptr %i.addr, align 4, !dbg !51
  %mul2 = mul nsw i32 %mul1, %4, !dbg !52
  store i32 %mul2, ptr %a, align 4, !dbg !47
  %5 = load i32, ptr %a, align 4, !dbg !53
  %6 = load i32, ptr %k.addr, align 4, !dbg !54
  call void @foo(i32 noundef 100, i32 noundef %5, i32 noundef %6, i32 noundef 800), !dbg !55
  ret void, !dbg !56
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @bar(i32 noundef %i, i32 noundef %j, i32 noundef %k) #0 !dbg !57 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  %k.addr = alloca i32, align 4
  store i32 %i, ptr %i.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %i.addr, metadata !58, metadata !DIExpression()), !dbg !59
  store i32 %j, ptr %j.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %j.addr, metadata !60, metadata !DIExpression()), !dbg !61
  store i32 %k, ptr %k.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %k.addr, metadata !62, metadata !DIExpression()), !dbg !63
  %0 = load i32, ptr %k.addr, align 4, !dbg !64
  %1 = load i32, ptr %i.addr, align 4, !dbg !65
  %mul = mul nsw i32 %0, %1, !dbg !66
  %div = sdiv i32 %mul, 2, !dbg !67
  store i32 %div, ptr %j.addr, align 4, !dbg !68
  %2 = load i32, ptr %j.addr, align 4, !dbg !69
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %2), !dbg !70
  ret void, !dbg !71
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(i32 noundef %i, i32 noundef %j, i32 noundef %k, i32 noundef %x) #0 !dbg !72 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  %k.addr = alloca i32, align 4
  %x.addr = alloca i32, align 4
  store i32 %i, ptr %i.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %i.addr, metadata !75, metadata !DIExpression()), !dbg !76
  store i32 %j, ptr %j.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %j.addr, metadata !77, metadata !DIExpression()), !dbg !78
  store i32 %k, ptr %k.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %k.addr, metadata !79, metadata !DIExpression()), !dbg !80
  store i32 %x, ptr %x.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x.addr, metadata !81, metadata !DIExpression()), !dbg !82
  %0 = load i32, ptr %i.addr, align 4, !dbg !83
  %1 = load i32, ptr %j.addr, align 4, !dbg !84
  %add = add nsw i32 %0, %1, !dbg !85
  %2 = load i32, ptr %k.addr, align 4, !dbg !86
  %add1 = add nsw i32 %add, %2, !dbg !87
  store i32 %add1, ptr %x.addr, align 4, !dbg !88
  %3 = load i32, ptr %x.addr, align 4, !dbg !89
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3), !dbg !90
  ret void, !dbg !91
}

declare i32 @printf(ptr noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 24, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "file5.c", directory: "/home/soumik/Documents/assignment-4(public)", checksumkind: CSK_MD5, checksum: "d7749395baf3218f17a11c76d15817a3")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 24, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 3)
!7 = distinct !DICompileUnit(language: DW_LANG_C11, file: !2, producer: "clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !8, splitDebugInlining: false, nameTableKind: None)
!8 = !{!0}
!9 = !{i32 7, !"Dwarf Version", i32 5}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{i32 8, !"PIC Level", i32 2}
!13 = !{i32 7, !"PIE Level", i32 2}
!14 = !{i32 7, !"uwtable", i32 2}
!15 = !{i32 7, !"frame-pointer", i32 2}
!16 = !{!"clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)"}
!17 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 6, type: !18, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!18 = !DISubroutineType(types: !19)
!19 = !{!20}
!20 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!21 = !{}
!22 = !DILocalVariable(name: "l", scope: !17, file: !2, line: 8, type: !20)
!23 = !DILocation(line: 8, column: 9, scope: !17)
!24 = !DILocation(line: 9, column: 5, scope: !17)
!25 = !DILocation(line: 10, column: 5, scope: !17)
!26 = !DILocation(line: 11, column: 25, scope: !17)
!27 = !DILocation(line: 11, column: 5, scope: !17)
!28 = !DILocation(line: 12, column: 1, scope: !17)
!29 = distinct !DISubprogram(name: "fun", scope: !2, file: !2, line: 13, type: !30, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!30 = !DISubroutineType(types: !31)
!31 = !{null, !20, !20, !20}
!32 = !DILocalVariable(name: "i", arg: 1, scope: !29, file: !2, line: 13, type: !20)
!33 = !DILocation(line: 13, column: 14, scope: !29)
!34 = !DILocalVariable(name: "j", arg: 2, scope: !29, file: !2, line: 13, type: !20)
!35 = !DILocation(line: 13, column: 21, scope: !29)
!36 = !DILocalVariable(name: "k", arg: 3, scope: !29, file: !2, line: 13, type: !20)
!37 = !DILocation(line: 13, column: 28, scope: !29)
!38 = !DILocation(line: 15, column: 15, scope: !29)
!39 = !DILocation(line: 15, column: 5, scope: !29)
!40 = !DILocalVariable(name: "o", scope: !29, file: !2, line: 16, type: !20)
!41 = !DILocation(line: 16, column: 9, scope: !29)
!42 = !DILocation(line: 16, column: 13, scope: !29)
!43 = !DILocation(line: 16, column: 15, scope: !29)
!44 = !DILocalVariable(name: "q", scope: !29, file: !2, line: 17, type: !20)
!45 = !DILocation(line: 17, column: 9, scope: !29)
!46 = !DILocalVariable(name: "a", scope: !29, file: !2, line: 18, type: !20)
!47 = !DILocation(line: 18, column: 9, scope: !29)
!48 = !DILocation(line: 18, column: 13, scope: !29)
!49 = !DILocation(line: 18, column: 17, scope: !29)
!50 = !DILocation(line: 18, column: 15, scope: !29)
!51 = !DILocation(line: 18, column: 21, scope: !29)
!52 = !DILocation(line: 18, column: 19, scope: !29)
!53 = !DILocation(line: 19, column: 14, scope: !29)
!54 = !DILocation(line: 19, column: 17, scope: !29)
!55 = !DILocation(line: 19, column: 5, scope: !29)
!56 = !DILocation(line: 20, column: 1, scope: !29)
!57 = distinct !DISubprogram(name: "bar", scope: !2, file: !2, line: 26, type: !30, scopeLine: 27, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!58 = !DILocalVariable(name: "i", arg: 1, scope: !57, file: !2, line: 26, type: !20)
!59 = !DILocation(line: 26, column: 14, scope: !57)
!60 = !DILocalVariable(name: "j", arg: 2, scope: !57, file: !2, line: 26, type: !20)
!61 = !DILocation(line: 26, column: 21, scope: !57)
!62 = !DILocalVariable(name: "k", arg: 3, scope: !57, file: !2, line: 26, type: !20)
!63 = !DILocation(line: 26, column: 28, scope: !57)
!64 = !DILocation(line: 28, column: 10, scope: !57)
!65 = !DILocation(line: 28, column: 12, scope: !57)
!66 = !DILocation(line: 28, column: 11, scope: !57)
!67 = !DILocation(line: 28, column: 14, scope: !57)
!68 = !DILocation(line: 28, column: 7, scope: !57)
!69 = !DILocation(line: 29, column: 18, scope: !57)
!70 = !DILocation(line: 29, column: 5, scope: !57)
!71 = !DILocation(line: 30, column: 1, scope: !57)
!72 = distinct !DISubprogram(name: "foo", scope: !2, file: !2, line: 21, type: !73, scopeLine: 22, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!73 = !DISubroutineType(types: !74)
!74 = !{null, !20, !20, !20, !20}
!75 = !DILocalVariable(name: "i", arg: 1, scope: !72, file: !2, line: 21, type: !20)
!76 = !DILocation(line: 21, column: 14, scope: !72)
!77 = !DILocalVariable(name: "j", arg: 2, scope: !72, file: !2, line: 21, type: !20)
!78 = !DILocation(line: 21, column: 21, scope: !72)
!79 = !DILocalVariable(name: "k", arg: 3, scope: !72, file: !2, line: 21, type: !20)
!80 = !DILocation(line: 21, column: 28, scope: !72)
!81 = !DILocalVariable(name: "x", arg: 4, scope: !72, file: !2, line: 21, type: !20)
!82 = !DILocation(line: 21, column: 35, scope: !72)
!83 = !DILocation(line: 23, column: 9, scope: !72)
!84 = !DILocation(line: 23, column: 11, scope: !72)
!85 = !DILocation(line: 23, column: 10, scope: !72)
!86 = !DILocation(line: 23, column: 13, scope: !72)
!87 = !DILocation(line: 23, column: 12, scope: !72)
!88 = !DILocation(line: 23, column: 7, scope: !72)
!89 = !DILocation(line: 24, column: 18, scope: !72)
!90 = !DILocation(line: 24, column: 5, scope: !72)
!91 = !DILocation(line: 25, column: 1, scope: !72)
