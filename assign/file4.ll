; ModuleID = 'file4.c'
source_filename = "file4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @compute(i32 noundef %a, i32 noundef %b) #0 !dbg !10 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %result = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 %b, ptr %b.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %b.addr, metadata !17, metadata !DIExpression()), !dbg !18
  tail call void @llvm.dbg.declare(metadata ptr %c, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 10, ptr %c, align 4, !dbg !20
  tail call void @llvm.dbg.declare(metadata ptr %d, metadata !21, metadata !DIExpression()), !dbg !22
  %0 = load i32, ptr %c, align 4, !dbg !23
  %add = add nsw i32 %0, 5, !dbg !24
  store i32 %add, ptr %d, align 4, !dbg !22
  tail call void @llvm.dbg.declare(metadata ptr %result, metadata !25, metadata !DIExpression()), !dbg !26
  %1 = load i32, ptr %a.addr, align 4, !dbg !27
  %2 = load i32, ptr %d, align 4, !dbg !28
  %mul = mul nsw i32 %1, %2, !dbg !29
  %3 = load i32, ptr %b.addr, align 4, !dbg !30
  %add1 = add nsw i32 %mul, %3, !dbg !31
  store i32 %add1, ptr %result, align 4, !dbg !26
  ret void, !dbg !32
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !33 {
entry:
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x, metadata !36, metadata !DIExpression()), !dbg !37
  store i32 19, ptr %x, align 4, !dbg !37
  tail call void @llvm.dbg.declare(metadata ptr %y, metadata !38, metadata !DIExpression()), !dbg !39
  %0 = load i32, ptr %x, align 4, !dbg !40
  %mul = mul nsw i32 %0, 90, !dbg !41
  store i32 %mul, ptr %y, align 4, !dbg !39
  %1 = load i32, ptr %x, align 4, !dbg !42
  %2 = load i32, ptr %y, align 4, !dbg !43
  call void @compute(i32 noundef %1, i32 noundef %2), !dbg !44
  ret i32 0, !dbg !45
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "file4.c", directory: "/home/soumik/Documents/assignment-4(public)", checksumkind: CSK_MD5, checksum: "e57faad35f16a173688c73cbb385d342")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)"}
!10 = distinct !DISubprogram(name: "compute", scope: !1, file: !1, line: 3, type: !11, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!11 = !DISubroutineType(types: !12)
!12 = !{null, !13, !13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !{}
!15 = !DILocalVariable(name: "a", arg: 1, scope: !10, file: !1, line: 3, type: !13)
!16 = !DILocation(line: 3, column: 18, scope: !10)
!17 = !DILocalVariable(name: "b", arg: 2, scope: !10, file: !1, line: 3, type: !13)
!18 = !DILocation(line: 3, column: 25, scope: !10)
!19 = !DILocalVariable(name: "c", scope: !10, file: !1, line: 4, type: !13)
!20 = !DILocation(line: 4, column: 9, scope: !10)
!21 = !DILocalVariable(name: "d", scope: !10, file: !1, line: 5, type: !13)
!22 = !DILocation(line: 5, column: 9, scope: !10)
!23 = !DILocation(line: 5, column: 13, scope: !10)
!24 = !DILocation(line: 5, column: 15, scope: !10)
!25 = !DILocalVariable(name: "result", scope: !10, file: !1, line: 6, type: !13)
!26 = !DILocation(line: 6, column: 9, scope: !10)
!27 = !DILocation(line: 6, column: 19, scope: !10)
!28 = !DILocation(line: 6, column: 23, scope: !10)
!29 = !DILocation(line: 6, column: 21, scope: !10)
!30 = !DILocation(line: 6, column: 27, scope: !10)
!31 = !DILocation(line: 6, column: 25, scope: !10)
!32 = !DILocation(line: 7, column: 1, scope: !10)
!33 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 8, type: !34, scopeLine: 9, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!34 = !DISubroutineType(types: !35)
!35 = !{!13}
!36 = !DILocalVariable(name: "x", scope: !33, file: !1, line: 10, type: !13)
!37 = !DILocation(line: 10, column: 6, scope: !33)
!38 = !DILocalVariable(name: "y", scope: !33, file: !1, line: 11, type: !13)
!39 = !DILocation(line: 11, column: 7, scope: !33)
!40 = !DILocation(line: 11, column: 11, scope: !33)
!41 = !DILocation(line: 11, column: 13, scope: !33)
!42 = !DILocation(line: 12, column: 10, scope: !33)
!43 = !DILocation(line: 12, column: 13, scope: !33)
!44 = !DILocation(line: 12, column: 2, scope: !33)
!45 = !DILocation(line: 13, column: 1, scope: !33)
